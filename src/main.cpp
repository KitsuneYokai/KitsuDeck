#include <lvgl.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <Arduino_GFX_Library.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ui/ui.h"
#include "utils/Screen.h"
#include "utils/WebServer.h"
#include "utils/settings.h"
#include "utils/ScreenMessages.h"

#define TFT_BL 2

void initializeLVGL(void *parameter)
{
  Serial.begin(115200);
  Serial.println("KitsuDeck v0.1 - ESP32 Lets Go!");
  // Init Display
  gfx->begin();
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  ledcSetup(0, 300, 8);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(0, 255);

  // Init SD Card
  if (!SD.begin())
  {
    // if the SD card is not found/initialize error, show error message on the screen
    errorSD();
  }
  // check if the settings file exists/valid
  bool settingsCheck = checkSettingsBool();
  if (!settingsCheck)
  {
    // create settings file
    createSettings();
  }

  ledcWrite(0, getSettings("brightness").toInt());

  // Init LVGL
  lv_init();

  /*Initialize the Touch */
  initSetupTouch();

  screenWidth = gfx->width();
  screenHeight = gfx->height();
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 4);

  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize touch driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
  ui_init();

  Serial.println("Setup done");

  // End of the task, delete itself
  vTaskDelete(NULL);
}

void setup()
{
  // Start the task that initializes LVGL
  xTaskCreatePinnedToCore(initializeLVGL, "lvgl_task", 8192, NULL, 1, NULL, 1);
  // Start the web server in a new task
  xTaskCreatePinnedToCore(startWebServer, "web_server", 8192, NULL, 1, NULL, 1);
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}