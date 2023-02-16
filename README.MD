
# KitsuDeck

KitsuDeck will be a makro keyboard for a ESP32 with a 7" touch screen display. 
It will be able to start programs on your pc, or invoke F13- F... keys / makros, or even
controll your spotify client.

I have some ideas for the future, but I will see how far I get with this project.

## Hardware

- [ESP32-8048S070](https://aliexpi.com/Xd6v) (7" touch screen) (other LVGL screens, with an ESP32 should work too, but I have not tested them yet, cause i have no other screens)
- [MB-102 MB102 DC 7-12V](https://aliexpi.com/YwtF) (Will work as a power supply for the ESP HMI, since the usb-c port is not enough on heavy operation, and the final design would look ugly with the usb-c port sticking out, i will make the usb-c port accessible with a cover tough, so its still accessible, but not visible)
  
- probably a 3case(will beD printed  uploaded later, when it is finished)
- powersupply (I have yet to find one, that fits the ESP HMI(using the usb-c port for now))
- maybe a battery in the future (idk about that yet)
- MicroSD card(worked with a 8GB one, but I have not tested it with larger ones yet) (format it to FAT. FAT32 should work too, but I have not tested it yet)

## Software

- [LVGL](https://lvgl.io/) (for the GUI)
- [PlatformIO](https://platformio.org/) (for the ESP32)
- [Visual Studio Code](https://code.visualstudio.com/) (for the IDE)
- [SquarelineStudio](https://squareline.io/) (for the GUI design)(source will be uploaded later, when it is finished)

## How to use
more info will be added later on since the project is still in development and there might be some changes 

## things to note

- The panel will crash on heavy load, when your pc usb output is not enough. To fix this, i attached a [MB-102 MB102 DC 7-12V](https://aliexpi.com/YwtF) to the 4Pin UART port of the Board, now it works ok, i have to find a better power supply for it tho, cause it only works with 50% brightness now(using JCY-1260 power cord(couldn't find a link, just google it its a led power supply)), but it is enough for development.
