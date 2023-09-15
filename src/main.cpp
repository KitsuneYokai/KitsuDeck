#include <WiFi.h>
#include <lvgl.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <Arduino_GFX_Library.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"

#include "ui/ui.h"
#include "utils/Screen.h"
#include "utils/WebServer/WebServer.h"
#include "utils/wifiUtils.h"
#include "utils/settings.h"
#include "utils/ScreenMessages.h"
#include "utils/Database/Sqlite.h"

#include "main.h"

#define TFT_BL 2
const int TASK_STACK_SIZE = 8192;

// file system functions

static void *sd_fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode)
{
  LV_UNUSED(drv);

  const char *flags = "";

  if (mode == LV_FS_MODE_WR)
    flags = FILE_WRITE;
  else if (mode == LV_FS_MODE_RD)
    flags = FILE_READ;
  else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
    flags = FILE_WRITE;

  File f = SD.open(path, flags);
  if (!f)
  {
    Serial.println("Failed to open file!");
    return NULL;
  }

  File *lf = new File{f};

  // make sure at the beginning
  // fp->seek(0);

  return (void *)lf;
}

static lv_fs_res_t sd_fs_close(lv_fs_drv_t *drv, void *file_p)
{
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  fp->close();

  delete (fp); // when close
  return LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_read(lv_fs_drv_t *drv, void *file_p, void *fileBuf, uint32_t btr, uint32_t *br)
{
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  *br = fp->read((uint8_t *)fileBuf, btr);

  return (int32_t)(*br) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw)
{
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  *bw = fp->write((const uint8_t *)buf, btw);

  return (int32_t)(*bw) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence)
{
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  SeekMode mode;
  if (whence == LV_FS_SEEK_SET)
    mode = SeekSet;
  else if (whence == LV_FS_SEEK_CUR)
    mode = SeekCur;
  else if (whence == LV_FS_SEEK_END)
    mode = SeekEnd;

  fp->seek(pos, mode);

  return LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p)
{
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  *pos_p = fp->position();

  return LV_FS_RES_OK;
}

static void *sd_dir_open(lv_fs_drv_t *drv, const char *dirpath)
{
  LV_UNUSED(drv);

  File root = SD.open(dirpath);
  if (!root)
  {
    Serial.println("Failed to open directory!");
    return NULL;
  }

  if (!root.isDirectory())
  {
    Serial.println("Not a directory!");
    return NULL;
  }

  File *lroot = new File{root};

  return (void *)lroot;
}

static lv_fs_res_t sd_dir_read(lv_fs_drv_t *drv, void *dir_p, char *fn)
{
  LV_UNUSED(drv);

  File *root = (File *)dir_p;
  fn[0] = '\0';

  File file = root->openNextFile();
  while (file)
  {
    if (strcmp(file.name(), ".") == 0 || strcmp(file.name(), "..") == 0)
    {
      continue;
    }
    else
    {
      if (file.isDirectory())
      {
        Serial.print("  DIR : ");
        Serial.println(file.name());
        fn[0] = '/';
        strcpy(&fn[1], file.name());
      }
      else
      {
        Serial.print("  FILE: ");
        Serial.print(file.name());
        Serial.print("  SIZE: ");
        Serial.println(file.size());

        strcpy(fn, file.name());
      }
      break;
    }
    file = root->openNextFile();
  }

  return LV_FS_RES_OK;
}

static lv_fs_res_t sd_dir_close(lv_fs_drv_t *drv, void *dir_p)
{
  LV_UNUSED(drv);

  File *root = (File *)dir_p;

  root->close();

  delete (root); // when close

  return LV_FS_RES_OK;
}

void initializeLVGL()
{
  Serial.begin(115200);
  Serial.println("KitsuDeck v" VERSION " - Lets Go!");

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
    errorSD();
  }
  // Check if the settings file exists/valid
  if (!checkSettingsBool())
  {
    createSettings();
  }
  // Set the brightness of the display to the value in the settings file
  ledcWrite(0, getSettings("brightness").toInt());

  // Init PSRAM
  if (!psramInit())
  {
    Serial.println("Error initializing PSRAM");
  }

  // Init LVGL
  lv_init();

  // Initialize the Touch
  initSetupTouch();
  screenWidth = gfx->width();
  screenHeight = gfx->height();
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight / 4, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, nullptr, screenWidth * screenHeight / 4);

  // Initialize the display
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Initialize touch driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // TODO: LVGL File Storage Setup (SD Card)
  /*Add a simple drive to open images*/
  static lv_fs_drv_t fs_drv;
  lv_fs_drv_init(&fs_drv);
  fs_drv.letter = 'S';
  fs_drv.cache_size = 0;
  fs_drv.open_cb = sd_fs_open;
  fs_drv.close_cb = sd_fs_close;
  fs_drv.read_cb = sd_fs_read;
  fs_drv.write_cb = sd_fs_write;
  fs_drv.seek_cb = sd_fs_seek;
  fs_drv.tell_cb = sd_fs_tell;
  fs_drv.dir_close_cb = sd_dir_close;
  fs_drv.dir_open_cb = sd_dir_open;
  fs_drv.dir_read_cb = sd_dir_read;
  lv_fs_drv_register(&fs_drv);

  // Initialize image decoders
  lv_png_init();
  lv_bmp_init();
  lv_split_jpeg_init();

  // Initialize the UI
  ui_init();

  Serial.println("LVGL Setup done");
}

void setup()
{
  // Initialize LVGL
  initializeLVGL();
  // Enable malloc in external memory
  heap_caps_malloc_extmem_enable(0);
  // Start the web server in a new task
  xTaskCreatePinnedToCore(
      startWebServer,
      "web_server",
      TASK_STACK_SIZE,
      nullptr,
      1,
      nullptr,
      1);
  initDatabase();
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(1);
}
