
# KitsuDeck

KitsuDeck will be a makro keyboard for a ESP32 with a 7" touch screen display.
(paused for now, waiting for aliexpress to ship the parts)
It will be able to start programs on your pc, or invoke F13- F... keys / makros, or even
controll your spotify client.

I have some ideas for the future, but I will see how far I get with this project.

## Hardware

- [ESP32-8048S070](https://aliexpi.com/Xd6v) (7" touch screen) (other LVGL screens, with an ESP32 should work too, but I have not tested them yet, cause i have no other screens)
- [MB-102 MB102 DC 7-12V](https://aliexpi.com/YwtF) (Will work as a power supply for the ESP HMI, since the usb-c port is not enough on heavy operation, and the final design would look ugly with the usb-c port sticking out, i will make the usb-c port accessible with a cover tough, so its still accessible, but not visible)
- [Power Brick](https://www.amazon.de/Offizielles-Amazon-PowerFast-W-USB-Ladegerät-Fire-Tablets/dp/B01I0IGFMK)(I used an amazon ps57cp but any power brick with similar ratings should work)
- probably a 3D printed case(will be uploaded later, when it is finished)
- MicroSD card(worked with a 8GB one, but I have not tested it with larger ones yet) (format it to FAT. FAT32 should work too, but I have not tested it yet)

## Software

- [LVGL](https://lvgl.io/) (for the GUI)
- [PlatformIO](https://platformio.org/) (for the ESP32)
- [Visual Studio Code](https://code.visualstudio.com/) (for the IDE)
- [SquarelineStudio](https://squareline.io/) (for the GUI design)(source will be uploaded later, when it is finished)

- [KitsuDeckDash](https://github.com/KitsuneYokai/KitsuDeckDash) (This is/will be the desktop application for the KitsuDeck to create new makros. It will also server as a "bridge" between the ESP32 and the PC, so the ESP32 can control the PC.")

## How to 
drop the `lv_conf.h` file into your .pio/libdeps/esp32s3box folder.

also make sure to use the GFX Library thats included in the resources folder, install it globally:
```
pio lib -g install .\resources\Arduino_GFX-master.zip
```

else there will be critical build errors.