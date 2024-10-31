# USB Midi Interface for Yamaha PSR E360
A simple midi out interface for yamaha psr e360 keyboard to use with music learning software on a tablet or pc (e.g. 'simply piano'). 
The software can recognize individual or multiple keys on the keyboard accurately and without delay
# Restrictions:
* No support for touch dynamics (just key is pressed or or not pressed)
* Midi in is not supported
# Requirements
* Yamaha PSR E360 Keyboard
* Arduino Leonardo (recommended) or any other Arduino/ESP32 dev board with native (!) USB on board
* Some wire
* Solder station
* Microscope (recommended)
* Micro usb cable and adapter for keyboard enclosure
* Some screws for fixing the Arduino

# How-To
1. Open the keyboard case
2. Remove the driver board
3. Wiring according the picture ![20220509_124445_verdrahtung_direkt](https://github.com/user-attachments/assets/9adffc1d-a2fc-4815-8e37-f4350df06015)
4. Upload the skretch zu arduino leonardo with the arduino ide
5. Install the usb adapter on the keyboard case
6. Test your input with the software VMPK
