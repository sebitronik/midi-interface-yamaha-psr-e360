# Usb Midi Interface for Yamaha PSR E360 with Arduino Leonardo
![title](https://github.com/user-attachments/assets/fb22b044-fd96-406b-8c8d-1585e3c415f6)

A simple MIDI interface for the Yamaha PSR E360 keyboard, designed for use with music learning software on a tablet or PC (e.g., "Simply Piano"). The software can recognize individual and multiple keys on the keyboard accurately and without delay.

## Requirements
* Yamaha PSR E360 Keyboard
* Arduino Leonardo or compatible, any other dev board which supports native USB HID functionality and has 18 free digital inputs
* Some very thin wrapping wire (AWG30), breadboard jumper wires, pin header
* Soldering stuff
* Screwdriver
* Microscope (optional)
* Micro USB cable and adapter for keyboard enclosure
* Some screws to fix the Arduino

## Restrictions
* No support for touch sensitivity (only whether a key is pressed or not)
* MIDI-In is not supported, only MIDI-Out

## Support me
[If you like, you can support me via PayPal](https://www.paypal.me/SebastianDiefenbach)

[![Donate with PayPal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.me/SebastianDiefenbach)

# Instructions
## Step 1: Preparations
Disconnect the power supply or batteries and open the keyboard case (note that this will void any remaining warranty). ![screws](https://github.com/user-attachments/assets/bbcd0ccd-3c16-4224-841f-c1229925b69e)

## Step 2: Remove the main board
Carefully remove the black cables by opening the white socket. It’s important to note the direction in which the cables are inserted so they can be reinserted the same way at the end (Hint: note the position of the white-marked cable). Now you can remove the screws and take the mainboard out of the case.  ![mainboard](https://github.com/user-attachments/assets/5ffe689c-2cd0-464d-83ab-ce3d05781627)

## Step 3: Soldering
Now for the tricky part: You can solder the wires from the backside of the board directly to the GPIO pins on the Arduino, or (like I did) attach a 19-pin header on the right side with some glue and solder the wires step-by-step under the microscope. Fortunately, ports D11–D7 of the pin header can be soldered directly to the board. If you use a other board than arduino make sure you have exact the same free GPIOs available as the leonardo otherwise you have to modifiy the code. ![connection_to_arduino](https://github.com/user-attachments/assets/76da28b1-f90a-4575-976f-b60961070ddb)
Here’s the result with jumper wires wrapped with some tape. ![20241101_175825](https://github.com/user-attachments/assets/99f6066c-b6df-4b57-8dee-ceb42ed1c81c)
Now carefully reinsert the black cables from before on the mainboard.

## Step 4: Programming 
1. Download the sketch from the release directory and start the Arduino IDE.
2. Connect the Arduino to the PC via USB cable, install the "MIDIUSB" library from the library manager in Arduino IDE, and upload the sketch to the Arduino.
3. Download VMPK https://vmpk.sourceforge.io, set the MIDI Interface to Arduino Leonardo, and test your inputs. Now you should see and hear your keyboard inputs on the computer. Note: If you are pressing one key you will instantly see it on the monitor but the sound on PC need some time to produce (its only a lag in sound output not in the interface). Therefore it is always better to mute the speakers on your monitor or tablet and hear the sound directly from the keyboard.

## Step 5: Final actions
Install a USB adapter on the keyboard case for external connection by drilling a hole in the case.  ![usb_adapter](https://github.com/user-attachments/assets/a71c92b3-18c8-4a13-b470-ad198eb77fa7) Now attach the Arduino to the case using screws, glue, or board holder clips, and reassemble the case. Congrats! You are ready to play!
![20241101_173311](https://github.com/user-attachments/assets/759cb362-0797-477e-993d-36c0537a5a3b)

# Some additional technical information

## Disturbance on column wires

The Yamaha keyboard sends a keystroke signal in rows and columns to the mainboard. This signal is then forwarded to the Arduino, where it determines which key has been pressed. Additionally, the keyboard has an extra switch for each key that is only triggered when the key is pressed further down. This information is used to enable velocity sensitivity (though this information is currently not utilized). Essentially, a simple query is made to forward the information via the MIDI protocol over USB. Unfortunately, there is a periodical interference signals for the column that must be filtered out because otherwise, the Arduino cannot clearly identify the key:
![SDS00011](https://github.com/user-attachments/assets/e0bc930c-3cb3-440b-b18b-5654e4cde0dd)

Here, we notice some peaks in the magenta signal (only in columns not in rows). If we looking closer, we occasionally see two impulses that are unnecessary, therefore making the filter in the code essential.
![SDS00005](https://github.com/user-attachments/assets/7000ef12-5318-4dc0-862b-7f0ae49ceaca)

## Fast polling of the GPIO Inputs

To read the state of the Arduino inputs, it became clear that the digitalRead() function was too slow, introducing a delay of several milliseconds. Therefore, direct register access (e.g., PIND & B00000100) is essential for efficiently determining the state. This method is significantly faster and better suited for sampling a 2 kHz signal, reducing the delay to just a few nanoseconds.
