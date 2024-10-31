# Usb Midi Interface for Yamaha PSR E360
![title](https://github.com/user-attachments/assets/5e19b155-ed9c-4c62-a946-06533dfe7f22)
A simple midi interface for yamaha psr e360 keyboard to use with music learning software on a tablet or pc (e.g. 'simply piano'). 
The software can recognize individual or multiple keys on the keyboard
 accurately and without delay

# Requirements
* Yamaha PSR E360 Keyboard
* Arduino Leonardo (recommended) or any other Arduino/ESP32 dev board with native USB HID functionality with 18 Digital Inputs
* Some wire
* Solder station
* Screwdriver
* Microscope (recommended)
* Micro usb cable and adapter for keyboard enclosure
* Some screws for fixing the Arduino

# Restrictions:
* No support for touch dynamics (just key is pressed or or not pressed)
* Midi in is not supported only midi out

# How-To
1. Open the keyboard case (Note that you will lose the remaining warranty) ![screws](https://github.com/user-attachments/assets/bbcd0ccd-3c16-4224-841f-c1229925b69e)
2. Carefully remove the black cables by opening the white socket. It's very important to note the direction in which the cables are inserted so that they can be reinserted in the same way at the end (Hint: note the position of the white marked cable)  ![mainboard](https://github.com/user-attachments/assets/5ffe689c-2cd0-464d-83ab-ce3d05781627)
3. Unscrew the screws and remove the mainboard
4. Now the more difficult part: You can solder the cables from backside of the board directly to an pin header on the GPIOs of the arduino or (like the picture) put on the right side of the Board an 19 PIN Header with some glue and solder the cables to that header step by step (From there you will need Jumper Wires to the Arduino Ports). The following picture shows you where you have solder the wires on the Board an in white the target GPIO Pin of the Arduino. Which way you prefer is your choice. ![20220509_124445_verdrahtung_direkt](https://github.com/user-attachments/assets/9adffc1d-a2fc-4815-8e37-f4350df06015) Here you can see the result with jumper wires (but as mentioned before this is optional) ![jumper_wires](https://github.com/user-attachments/assets/0a221dd5-db40-4e67-966b-9aded31f5ab2)
5. Carefully reinsert the black cables from before 
6. Download the Skretch from release directory and upload it to arduino leonardo with the arduino ide
7. Connect your PC with an USB Cable and test your midi interface on PC with the free Software e.g. VMPK [(https://vmpk.sourceforge.io)]
8. Install the usb adapter on the keyboard case for the outside world ![usb_adapter](https://github.com/user-attachments/assets/a71c92b3-18c8-4a13-b470-ad198eb77fa7)
9. Attach the arduino on case with some screws, glue or board holder clips
10. Congratulation! You are ready to play!
