# Usb Midi Interface for Yamaha PSR E360
![title](https://github.com/user-attachments/assets/5e19b155-ed9c-4c62-a946-06533dfe7f22)
A simple MIDI interface for the Yamaha PSR E360 keyboard, designed for use with music learning software on a tablet or PC (e.g., "Simply Piano"). The software can recognize individual or multiple keys on the keyboard accurately and without delay.

# Requirements
* Yamaha PSR E360 Keyboard
* Arduino Leonardo (recommended) or any other Arduino/ESP32 dev board with native USB HID functionality and 18 digital inputs
* Some very thin wrapping wire (AWG30), breadboard jumper wires, pin header
* Soldering stuff
* Screwdriver
* Microscope (optional)
* Micro USB cable and adapter for keyboard enclosure
* Some screws to fix the Arduino

# Restrictions:
* No support for touch sensitivity (only whether a key is pressed or not)
* MIDI-In is not supported, only MIDI-Out

# Instruction
Step 1:
Disconnect the power supply or batteries and open the keyboard case (note that this will void any remaining warranty). ![screws](https://github.com/user-attachments/assets/bbcd0ccd-3c16-4224-841f-c1229925b69e)

Step 2: 
Carefully remove the black cables by opening the white socket. It’s important to note the direction in which the cables are inserted so they can be reinserted the same way at the end (Hint: note the position of the white-marked cable). Now you can remove the screws and take the mainboard out of the case.  ![mainboard](https://github.com/user-attachments/assets/5ffe689c-2cd0-464d-83ab-ce3d05781627)

Step 3: 
Now for the tricky part: You can solder the wires from the backside of the board directly to the GPIO pins on the Arduino, or (like I did) attach a 19-pin header on the right side with some glue and solder the wires step-by-step under the microscope. Fortunately, ports D11–D7 can be soldered directly to the board. ![connection_to_arduino](https://github.com/user-attachments/assets/76da28b1-f90a-4575-976f-b60961070ddb)
Here’s the result with jumper wires wrapped with some tape. ![jumper_wires](https://github.com/user-attachments/assets/0a221dd5-db40-4e67-966b-9aded31f5ab2)

Step 4: 
Now carefully reinsert the black cables from before on the mainboard.

Step 5: 
Download the sketch from the release directory and start the Arduino IDE.

Step 6: 
Connect the Arduino to the PC via USB cable, install the "MIDIUSB" library from the library manager in Arduino IDE, and upload the sketch to the Arduino.

Step 7: 
Download VMPK https://vmpk.sourceforge.io, set the MIDI Interface to Arduino Leonardo, and test your inputs. You should see and hear your keyboard inputs from PC.

Step 8: 
Install the USB adapter on the keyboard case for external connection. ![usb_adapter](https://github.com/user-attachments/assets/a71c92b3-18c8-4a13-b470-ad198eb77fa7)

Step 9: 
Attach the Arduino to the case using screws, glue, or board holder clips, and reassemble the case.

Step 10: 
Congrats! You are ready to play!

# Technical Background

## Disturbance on Row lines:

The keyboard sends a keystroke signal in rows and columns to the mainboard. This signal is then forwarded to the Arduino, where it determines which key has been pressed. Additionally, the keyboard has an extra switch for each key that is only triggered when the key is pressed further down. This information is used to enable velocity sensitivity (though this information is currently not utilized). Essentially, a simple query is made to forward the information via the MIDI protocol over USB. Unfortunately, there is interference on the signals for the rows that must be filtered out because otherwise, the Arduino cannot clearly identify the key:![filter](https://github.com/user-attachments/assets/7516936b-1a3a-4605-a4fe-ddfbf5e1219d)

Sometimes the yellow row signal has two impulses.

## Fast polling of the GPIO Inputs:

To read the state of the Arduino inputs, it was clear that using digitalRead() function is too slow, with a delay of some milliseconds. Therefore, direct register access is essential (e.g. `PIND & B00000100`) to efficiently determine the state. This method is much faster and better suited for sampling a 2 kHz signal now with a delay of some nanoseconds.
