# A midi interface for yamaha psr e360
A simple midi out interface for yamaha psr e360 b keyboard to use with music learning software on a tablet or pc (e.g. 'simply piano'). 
The software can recognize individual or multiple keys on the keyboard accurately and without delay
# Restrictions:
* no support for touch dynamics (just on or off)
* no support midi in
# Requirements
* Arduino Leonardo (recommended) or any other arduino/esp32 dev board with native usb on board
* some wire
* solder station
* microscope (recommended)
* micro usb cable and adapter for keyboard enclosure
* some screws for fixing the arduino

# How-To
1. Open the keyboard case
2. remove the driver board
3. Wiring according the picture ![20220509_124445_verdrahtung_direkt](https://github.com/user-attachments/assets/9adffc1d-a2fc-4815-8e37-f4350df06015)
4. Upload the skretch zu arduino leonardo with the arduino ide
5. Install the usb adapter on the keyboard case
6. Test your input with the software VMPK
