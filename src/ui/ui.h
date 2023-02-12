// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: KitsuDeck

#ifndef _KITSUDECK_UI_H
#define _KITSUDECK_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "lvgl.h"

void ui_event_Home( lv_event_t * e);
extern lv_obj_t *ui_Home;
extern lv_obj_t *ui_Navbar;
extern lv_obj_t *ui_Clock;
extern lv_obj_t *ui_Panel1;
extern lv_obj_t *ui_ImgButton3;
void ui_event_SettingsBtn( lv_event_t * e);
extern lv_obj_t *ui_SettingsBtn;
extern lv_obj_t *ui_DeckCol;
extern lv_obj_t *ui_ImgButton1;
void ui_event_SettingsView( lv_event_t * e);
extern lv_obj_t *ui_SettingsView;
void ui_event_SettingsHeaderPanel( lv_event_t * e);
extern lv_obj_t *ui_SettingsHeaderPanel;
void ui_event_SettingsBackToHome( lv_event_t * e);
extern lv_obj_t *ui_SettingsBackToHome;
extern lv_obj_t *ui_SettingsHeader;
void ui_event_SettingsPanel( lv_event_t * e);
extern lv_obj_t *ui_SettingsPanel;
extern lv_obj_t *ui_WifiConnect;
extern lv_obj_t *ui_WifiHeader;
extern lv_obj_t *ui_WifiSsidRoller;
void ui_event_WifiPasswordTextInput( lv_event_t * e);
extern lv_obj_t *ui_WifiPasswordTextInput;
extern lv_obj_t *ui_ButtonPanel;
void ui_event_WifiScanButton( lv_event_t * e);
extern lv_obj_t *ui_WifiScanButton;
extern lv_obj_t *ui_WifiScanText;
void ui_event_WifiSaveButton( lv_event_t * e);
extern lv_obj_t *ui_WifiSaveButton;
extern lv_obj_t *ui_WifiSaveText;
extern lv_obj_t *ui_WifiTestResultLabel;
extern lv_obj_t *ui_ButtonPanel2;
void ui_event_TestWifiSettingsButton( lv_event_t * e);
extern lv_obj_t *ui_TestWifiSettingsButton;
extern lv_obj_t *ui_TestWifiSettingsText;
extern lv_obj_t *ui_ComputerSettings;
extern lv_obj_t *ui_ComputerSettingsHeader;
void ui_event_ComputerIpInput( lv_event_t * e);
extern lv_obj_t *ui_ComputerIpInput;
extern lv_obj_t *ui_AuthHeading;
void ui_event_ComputerAuthUsername( lv_event_t * e);
extern lv_obj_t *ui_ComputerAuthUsername;
void ui_event_ComputerAuthPassword( lv_event_t * e);
extern lv_obj_t *ui_ComputerAuthPassword;
void ui_event_ComputerSaveButton( lv_event_t * e);
extern lv_obj_t *ui_ComputerSaveButton;
extern lv_obj_t *ui_ComputerSaveText;
extern lv_obj_t *ui_DeviceSettings;
extern lv_obj_t *ui_DeviceSettingsHeader;
extern lv_obj_t *ui_Label2;
void ui_event_ScreenBrightnessArk( lv_event_t * e);
extern lv_obj_t *ui_ScreenBrightnessArk;
extern lv_obj_t *ui_SettingsKeyboardText;

void initHome(lv_event_t * e);
void initSettings(lv_event_t * e);
void ScanWifiSsid(lv_event_t * e);
void SaveWifiSettings(lv_event_t * e);
void TestWifiSettings(lv_event_t * e);
void SaveComputerSettings(lv_event_t * e);
void saveSettingsBrightnessArkValue(lv_event_t * e);

LV_IMG_DECLARE( ui_img_deckimg_png);   // assets/deckImg.png
LV_IMG_DECLARE( ui_img_gear_png);   // assets/gear.png
LV_IMG_DECLARE( ui_img_b2_png);   // assets/b2.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
