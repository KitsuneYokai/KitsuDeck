#ifndef _SCREEN_H
#define _SCREEN_H

#include <lvgl.h>
#include <Arduino_GFX_Library.h>

static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

// define the *gfx value from the main.cpp file
extern Arduino_ESP32RGBPanel *bus;
extern Arduino_RPi_DPI_RGBPanel *gfx;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

void setLCDBrightness(int brightness);

void initSetupTouch();

#endif