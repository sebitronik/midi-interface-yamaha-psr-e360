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
* Microscope (recommended)
* Micro usb cable and adapter for keyboard enclosure
* Some screws for fixing the Arduino

# Restrictions:
* No support for touch dynamics (just key is pressed or or not pressed)
* Midi in is not supported only midi out

# How-To
1. Open the keyboard case (Note that you will lose the remaining warranty) ![screws](https://github.com/user-attachments/assets/bbcd0ccd-3c16-4224-841f-c1229925b69e)
2. Carefully removing the black cables from driver board
3. Remove driver board
4. Solder wires on the backside of the driverboard to the Arduino
5. Wiring according the picture ![20220509_124445_verdrahtung_direkt](https://github.com/user-attachments/assets/9adffc1d-a2fc-4815-8e37-f4350df06015)
6. Upload the skretch zu arduino leonardo with the arduino ide
7. Install the usb adapter on the keyboard case
8. Test your input with the software VMPK
