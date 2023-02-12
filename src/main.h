#ifndef _MAIN_H
#define _MAIN_H
#include <Arduino_GFX_Library.h>

// define the *gfx value from the main.cpp file
extern Arduino_ESP32RGBPanel *bus;
extern Arduino_RPi_DPI_RGBPanel *gfx;

void setLCDBrightness(int brightness);

#endif
