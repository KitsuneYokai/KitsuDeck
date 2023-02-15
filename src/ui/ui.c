// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: KitsuDeck

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ui_event_Home( lv_event_t * e);
lv_obj_t *ui_Home;
lv_obj_t *ui_Navbar;
lv_obj_t *ui_Clock;
lv_obj_t *ui_Panel1;
lv_obj_t *ui_ImgButton3;
void ui_event_SettingsBtn( lv_event_t * e);
lv_obj_t *ui_SettingsBtn;
lv_obj_t *ui_DeckCol;
lv_obj_t *ui_ImgButton1;
void ui_event_SettingsView( lv_event_t * e);
lv_obj_t *ui_SettingsView;
void ui_event_SettingsHeaderPanel( lv_event_t * e);
lv_obj_t *ui_SettingsHeaderPanel;
void ui_event_SettingsBackToHome( lv_event_t * e);
lv_obj_t *ui_SettingsBackToHome;
lv_obj_t *ui_SettingsHeader;
void ui_event_SettingsPanel( lv_event_t * e);
lv_obj_t *ui_SettingsPanel;
lv_obj_t *ui_WifiConnect;
lv_obj_t *ui_WifiHeader;
lv_obj_t *ui_WifiSsidRoller;
void ui_event_WifiPasswordTextInput( lv_event_t * e);
lv_obj_t *ui_WifiPasswordTextInput;
lv_obj_t *ui_ButtonPanel;
void ui_event_WifiScanButton( lv_event_t * e);
lv_obj_t *ui_WifiScanButton;
lv_obj_t *ui_WifiScanText;
void ui_event_WifiSaveButton( lv_event_t * e);
lv_obj_t *ui_WifiSaveButton;
lv_obj_t *ui_WifiSaveText;
lv_obj_t *ui_WifiTestResultLabel;
lv_obj_t *ui_ButtonPanel2;
void ui_event_TestWifiSettingsButton( lv_event_t * e);
lv_obj_t *ui_TestWifiSettingsButton;
lv_obj_t *ui_TestWifiSettingsText;
lv_obj_t *ui_ComputerSettings;
lv_obj_t *ui_ComputerSettingsHeader;
lv_obj_t *ui_AuthHeading;
void ui_event_ComputerAuthUsername( lv_event_t * e);
lv_obj_t *ui_ComputerAuthUsername;
void ui_event_ComputerAuthPassword( lv_event_t * e);
lv_obj_t *ui_ComputerAuthPassword;
void ui_event_ComputerSaveButton( lv_event_t * e);
lv_obj_t *ui_ComputerSaveButton;
lv_obj_t *ui_ComputerSaveText;
lv_obj_t *ui_DeviceSettings;
lv_obj_t *ui_DeviceSettingsHeader;
lv_obj_t *ui_Label2;
void ui_event_ScreenBrightnessArk( lv_event_t * e);
lv_obj_t *ui_ScreenBrightnessArk;
lv_obj_t *ui_SettingsKeyboardText;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Home( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      initHome( e );
}
}
void ui_event_SettingsBtn( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( ui_SettingsView, LV_SCR_LOAD_ANIM_OVER_LEFT, 500, 0);
}
}
void ui_event_SettingsView( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_SCREEN_LOADED) {
      initSettings( e );
}
}
void ui_event_SettingsHeaderPanel( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}
}
void ui_event_SettingsBackToHome( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( ui_Home, LV_SCR_LOAD_ANIM_OVER_RIGHT, 500, 0);
}
}
void ui_event_SettingsPanel( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}
}
void ui_event_WifiPasswordTextInput( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}
if ( event_code == LV_EVENT_PRESSED) {
      _ui_keyboard_set_target(ui_SettingsKeyboardText,  ui_WifiPasswordTextInput);
}
}
void ui_event_WifiScanButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_RELEASED) {
      ScanWifiSsid( e );
}
if ( event_code == LV_EVENT_RELEASED) {
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}
}
void ui_event_WifiSaveButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_RELEASED) {
      SaveWifiSettings( e );
}
if ( event_code == LV_EVENT_RELEASED) {
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}
}
void ui_event_TestWifiSettingsButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_RELEASED) {
      TestWifiSettings( e );
}
}
void ui_event_ComputerAuthUsername( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}
if ( event_code == LV_EVENT_PRESSED) {
      _ui_keyboard_set_target(ui_SettingsKeyboardText,  ui_ComputerAuthUsername);
}
}
void ui_event_ComputerAuthPassword( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}
if ( event_code == LV_EVENT_PRESSED) {
      _ui_keyboard_set_target(ui_SettingsKeyboardText,  ui_ComputerAuthPassword);
}
}
void ui_event_ComputerSaveButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_RELEASED) {
      SaveComputerSettings( e );
      _ui_flag_modify( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
}
}
void ui_event_ScreenBrightnessArk( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      setSettingsBrightnessArkValue( e );
}
if ( event_code == LV_EVENT_RELEASED) {
      saveSettingsBrightnessArkValue( e );
}
}

///////////////////// SCREENS ////////////////////
void ui_Home_screen_init(void)
{
ui_Home = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Home, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_flex_flow(ui_Home,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Home, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_BETWEEN);
lv_obj_set_style_pad_left(ui_Home, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Home, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Home, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Home, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Navbar = lv_obj_create(ui_Home);
lv_obj_set_width( ui_Navbar, lv_pct(15));
lv_obj_set_height( ui_Navbar, lv_pct(100));
lv_obj_set_x( ui_Navbar, -20 );
lv_obj_set_y( ui_Navbar, -19 );
lv_obj_set_align( ui_Navbar, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Navbar,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Navbar, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Navbar, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Navbar, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Navbar, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_Navbar, LV_BORDER_SIDE_NONE, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_pad_left(ui_Navbar, 10, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Navbar, 10, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Navbar, 0, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Navbar, 100, LV_PART_SCROLLBAR| LV_STATE_DEFAULT);

ui_Clock = lv_label_create(ui_Navbar);
lv_obj_set_width( ui_Clock, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_Clock, LV_SIZE_CONTENT);   /// 100
lv_obj_set_align( ui_Clock, LV_ALIGN_CENTER );
lv_label_set_text(ui_Clock,"12:30");
lv_obj_set_style_text_align(ui_Clock, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Clock, &lv_font_montserrat_40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel1 = lv_obj_create(ui_Navbar);
lv_obj_set_width( ui_Panel1, 130);
lv_obj_set_flex_grow( ui_Panel1, 1);
lv_obj_set_x( ui_Panel1, -85 );
lv_obj_set_y( ui_Panel1, -54 );
lv_obj_set_align( ui_Panel1, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel1,LV_FLEX_FLOW_ROW_WRAP);
lv_obj_set_flex_align(ui_Panel1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_Panel1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgButton3 = lv_imgbtn_create(ui_Panel1);
lv_imgbtn_set_src(ui_ImgButton3, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_deckimg_png, NULL);
lv_imgbtn_set_src(ui_ImgButton3, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_deckimg_png, NULL);
lv_obj_set_height( ui_ImgButton3, 64);
lv_obj_set_width( ui_ImgButton3, LV_SIZE_CONTENT);  /// 1
lv_obj_set_align( ui_ImgButton3, LV_ALIGN_CENTER );
lv_obj_set_style_img_recolor(ui_ImgButton3, lv_color_hex(0x292831), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_ImgButton3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor(ui_ImgButton3, lv_color_hex(0xFFFFFF), LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_img_recolor_opa(ui_ImgButton3, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_SettingsBtn = lv_imgbtn_create(ui_Navbar);
lv_imgbtn_set_src(ui_SettingsBtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_gear_png, NULL);
lv_imgbtn_set_src(ui_SettingsBtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_gear_png, NULL);
lv_obj_set_height( ui_SettingsBtn, 64);
lv_obj_set_width( ui_SettingsBtn, LV_SIZE_CONTENT);  /// 1
lv_obj_set_align( ui_SettingsBtn, LV_ALIGN_CENTER );
lv_obj_set_style_img_recolor(ui_SettingsBtn, lv_color_hex(0xFFFFFF), LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_img_recolor_opa(ui_SettingsBtn, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_DeckCol = lv_obj_create(ui_Home);
lv_obj_set_height( ui_DeckCol, lv_pct(100));
lv_obj_set_flex_grow( ui_DeckCol, 1);
lv_obj_set_x( ui_DeckCol, 19 );
lv_obj_set_y( ui_DeckCol, 182 );
lv_obj_set_align( ui_DeckCol, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_DeckCol,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_DeckCol, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_clear_flag( ui_DeckCol, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_ImgButton1 = lv_imgbtn_create(ui_DeckCol);
lv_obj_set_height( ui_ImgButton1, 64);
lv_obj_set_width( ui_ImgButton1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_align( ui_ImgButton1, LV_ALIGN_CENTER );

lv_obj_add_event_cb(ui_SettingsBtn, ui_event_SettingsBtn, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Home, ui_event_Home, LV_EVENT_ALL, NULL);

}
void ui_SettingsView_screen_init(void)
{
ui_SettingsView = lv_obj_create(NULL);
lv_obj_clear_flag( ui_SettingsView, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_flex_flow(ui_SettingsView,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_SettingsView, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_set_style_pad_left(ui_SettingsView, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_SettingsView, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_SettingsView, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_SettingsView, 10, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SettingsHeaderPanel = lv_obj_create(ui_SettingsView);
lv_obj_set_width( ui_SettingsHeaderPanel, lv_pct(100));
lv_obj_set_height( ui_SettingsHeaderPanel, LV_SIZE_CONTENT);   /// 50
lv_obj_set_align( ui_SettingsHeaderPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_SettingsHeaderPanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_SettingsHeaderPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_SettingsHeaderPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_SettingsBackToHome = lv_imgbtn_create(ui_SettingsHeaderPanel);
lv_imgbtn_set_src(ui_SettingsBackToHome, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_b2_png, NULL);
lv_imgbtn_set_src(ui_SettingsBackToHome, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_b2_png, NULL);
lv_obj_set_height( ui_SettingsBackToHome, 32);
lv_obj_set_width( ui_SettingsBackToHome, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_SettingsBackToHome, -1 );
lv_obj_set_y( ui_SettingsBackToHome, 34 );
lv_obj_set_align( ui_SettingsBackToHome, LV_ALIGN_CENTER );
lv_obj_set_style_img_recolor(ui_SettingsBackToHome, lv_color_hex(0x101418), LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_img_recolor_opa(ui_SettingsBackToHome, 255, LV_PART_MAIN| LV_STATE_PRESSED);

ui_SettingsHeader = lv_label_create(ui_SettingsHeaderPanel);
lv_obj_set_width( ui_SettingsHeader, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SettingsHeader, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_SettingsHeader, LV_ALIGN_CENTER );
lv_label_set_text(ui_SettingsHeader,"Settings");
lv_obj_set_style_text_font(ui_SettingsHeader, &lv_font_montserrat_38, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SettingsPanel = lv_obj_create(ui_SettingsView);
lv_obj_set_width( ui_SettingsPanel, lv_pct(100));
lv_obj_set_flex_grow( ui_SettingsPanel, 1);
lv_obj_set_x( ui_SettingsPanel, -176 );
lv_obj_set_y( ui_SettingsPanel, -209 );
lv_obj_set_align( ui_SettingsPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_SettingsPanel,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_SettingsPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_add_flag( ui_SettingsPanel, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS | LV_OBJ_FLAG_SCROLL_ONE );   /// Flags
lv_obj_clear_flag( ui_SettingsPanel, LV_OBJ_FLAG_SCROLL_MOMENTUM );    /// Flags
lv_obj_set_scroll_dir(ui_SettingsPanel, LV_DIR_HOR);
lv_obj_set_style_bg_color(ui_SettingsPanel, lv_color_hex(0x101418), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_SettingsPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_SettingsPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_WifiConnect = lv_obj_create(ui_SettingsPanel);
lv_obj_set_height( ui_WifiConnect, lv_pct(100));
lv_obj_set_width( ui_WifiConnect, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_WifiConnect, 79 );
lv_obj_set_y( ui_WifiConnect, -726 );
lv_obj_set_align( ui_WifiConnect, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_WifiConnect,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_WifiConnect, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

ui_WifiHeader = lv_label_create(ui_WifiConnect);
lv_obj_set_width( ui_WifiHeader, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_WifiHeader, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_WifiHeader, LV_ALIGN_CENTER );
lv_label_set_text(ui_WifiHeader,"Wifi settings:");
lv_obj_set_style_text_font(ui_WifiHeader, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_WifiSsidRoller = lv_roller_create(ui_WifiConnect);
lv_obj_set_width( ui_WifiSsidRoller, 200);
lv_obj_set_height( ui_WifiSsidRoller, lv_pct(45));
lv_obj_set_align( ui_WifiSsidRoller, LV_ALIGN_CENTER );

ui_WifiPasswordTextInput = lv_textarea_create(ui_WifiConnect);
lv_obj_set_width( ui_WifiPasswordTextInput, 200);
lv_obj_set_height( ui_WifiPasswordTextInput, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_WifiPasswordTextInput, -45 );
lv_obj_set_y( ui_WifiPasswordTextInput, 2 );
lv_obj_set_align( ui_WifiPasswordTextInput, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_WifiPasswordTextInput,"Password");
lv_textarea_set_one_line(ui_WifiPasswordTextInput,true);
lv_textarea_set_password_mode(ui_WifiPasswordTextInput, true);

ui_ButtonPanel = lv_obj_create(ui_WifiConnect);
lv_obj_set_width( ui_ButtonPanel, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_ButtonPanel, LV_SIZE_CONTENT);   /// 15
lv_obj_set_align( ui_ButtonPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ButtonPanel,LV_FLEX_FLOW_ROW_WRAP);
lv_obj_set_flex_align(ui_ButtonPanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_clear_flag( ui_ButtonPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_WifiScanButton = lv_btn_create(ui_ButtonPanel);
lv_obj_set_height( ui_WifiScanButton, 40);
lv_obj_set_width( ui_WifiScanButton, LV_SIZE_CONTENT);  /// 100
lv_obj_set_align( ui_WifiScanButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_WifiScanButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_WifiScanButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_WifiScanText = lv_label_create(ui_WifiScanButton);
lv_obj_set_width( ui_WifiScanText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_WifiScanText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_WifiScanText, LV_ALIGN_CENTER );
lv_label_set_text(ui_WifiScanText,"Scan");

ui_WifiSaveButton = lv_btn_create(ui_ButtonPanel);
lv_obj_set_height( ui_WifiSaveButton, 40);
lv_obj_set_width( ui_WifiSaveButton, LV_SIZE_CONTENT);  /// 100
lv_obj_set_align( ui_WifiSaveButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_WifiSaveButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_WifiSaveButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_WifiSaveText = lv_label_create(ui_WifiSaveButton);
lv_obj_set_width( ui_WifiSaveText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_WifiSaveText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_WifiSaveText, LV_ALIGN_CENTER );
lv_label_set_text(ui_WifiSaveText,"Save");

ui_WifiTestResultLabel = lv_label_create(ui_WifiConnect);
lv_obj_set_width( ui_WifiTestResultLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_WifiTestResultLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_WifiTestResultLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_WifiTestResultLabel,"");

ui_ButtonPanel2 = lv_obj_create(ui_WifiConnect);
lv_obj_set_width( ui_ButtonPanel2, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_ButtonPanel2, LV_SIZE_CONTENT);   /// 15
lv_obj_set_align( ui_ButtonPanel2, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ButtonPanel2,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_ButtonPanel2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
lv_obj_clear_flag( ui_ButtonPanel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_TestWifiSettingsButton = lv_btn_create(ui_ButtonPanel2);
lv_obj_set_height( ui_TestWifiSettingsButton, 40);
lv_obj_set_width( ui_TestWifiSettingsButton, LV_SIZE_CONTENT);  /// 100
lv_obj_set_align( ui_TestWifiSettingsButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_TestWifiSettingsButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_TestWifiSettingsButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_TestWifiSettingsText = lv_label_create(ui_TestWifiSettingsButton);
lv_obj_set_width( ui_TestWifiSettingsText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TestWifiSettingsText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_TestWifiSettingsText, LV_ALIGN_CENTER );
lv_label_set_text(ui_TestWifiSettingsText,"Test");

ui_ComputerSettings = lv_obj_create(ui_SettingsPanel);
lv_obj_set_height( ui_ComputerSettings, lv_pct(100));
lv_obj_set_width( ui_ComputerSettings, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ComputerSettings, 48 );
lv_obj_set_y( ui_ComputerSettings, -431 );
lv_obj_set_align( ui_ComputerSettings, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ComputerSettings,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_ComputerSettings, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);

ui_ComputerSettingsHeader = lv_label_create(ui_ComputerSettings);
lv_obj_set_width( ui_ComputerSettingsHeader, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ComputerSettingsHeader, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ComputerSettingsHeader, LV_ALIGN_CENTER );
lv_label_set_text(ui_ComputerSettingsHeader,"Computer settings:");
lv_obj_set_style_text_font(ui_ComputerSettingsHeader, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AuthHeading = lv_label_create(ui_ComputerSettings);
lv_obj_set_width( ui_AuthHeading, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AuthHeading, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_AuthHeading, LV_ALIGN_CENTER );
lv_label_set_text(ui_AuthHeading,"Auth:");

ui_ComputerAuthUsername = lv_textarea_create(ui_ComputerSettings);
lv_obj_set_width( ui_ComputerAuthUsername, 200);
lv_obj_set_height( ui_ComputerAuthUsername, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ComputerAuthUsername, -45 );
lv_obj_set_y( ui_ComputerAuthUsername, 2 );
lv_obj_set_align( ui_ComputerAuthUsername, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_ComputerAuthUsername,"Admin");
lv_textarea_set_one_line(ui_ComputerAuthUsername,true);

ui_ComputerAuthPassword = lv_textarea_create(ui_ComputerSettings);
lv_obj_set_width( ui_ComputerAuthPassword, 200);
lv_obj_set_height( ui_ComputerAuthPassword, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ComputerAuthPassword, -45 );
lv_obj_set_y( ui_ComputerAuthPassword, 2 );
lv_obj_set_align( ui_ComputerAuthPassword, LV_ALIGN_CENTER );
lv_textarea_set_placeholder_text(ui_ComputerAuthPassword,"Secure Password");
lv_textarea_set_one_line(ui_ComputerAuthPassword,true);
lv_textarea_set_password_mode(ui_ComputerAuthPassword, true);

ui_ComputerSaveButton = lv_btn_create(ui_ComputerSettings);
lv_obj_set_height( ui_ComputerSaveButton, 40);
lv_obj_set_width( ui_ComputerSaveButton, LV_SIZE_CONTENT);  /// 100
lv_obj_set_x( ui_ComputerSaveButton, 261 );
lv_obj_set_y( ui_ComputerSaveButton, -52 );
lv_obj_set_align( ui_ComputerSaveButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ComputerSaveButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ComputerSaveButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_ComputerSaveText = lv_label_create(ui_ComputerSaveButton);
lv_obj_set_width( ui_ComputerSaveText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ComputerSaveText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ComputerSaveText, LV_ALIGN_CENTER );
lv_label_set_text(ui_ComputerSaveText,"Save");

ui_DeviceSettings = lv_obj_create(ui_SettingsPanel);
lv_obj_set_height( ui_DeviceSettings, lv_pct(100));
lv_obj_set_width( ui_DeviceSettings, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_DeviceSettings, -19 );
lv_obj_set_y( ui_DeviceSettings, -433 );
lv_obj_set_align( ui_DeviceSettings, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_DeviceSettings,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_DeviceSettings, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

ui_DeviceSettingsHeader = lv_label_create(ui_DeviceSettings);
lv_obj_set_width( ui_DeviceSettingsHeader, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_DeviceSettingsHeader, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_DeviceSettingsHeader, LV_ALIGN_CENTER );
lv_label_set_text(ui_DeviceSettingsHeader,"Device Settings:");
lv_obj_set_style_text_font(ui_DeviceSettingsHeader, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label2 = lv_label_create(ui_DeviceSettings);
lv_obj_set_width( ui_Label2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label2, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label2,"Brightness");

ui_ScreenBrightnessArk = lv_arc_create(ui_DeviceSettings);
lv_obj_set_width( ui_ScreenBrightnessArk, 150);
lv_obj_set_height( ui_ScreenBrightnessArk, 150);
lv_obj_set_align( ui_ScreenBrightnessArk, LV_ALIGN_CENTER );

ui_SettingsKeyboardText = lv_keyboard_create(ui_SettingsView);
lv_obj_set_width( ui_SettingsKeyboardText, lv_pct(100));
lv_obj_set_height( ui_SettingsKeyboardText, lv_pct(40));
lv_obj_set_x( ui_SettingsKeyboardText, 0 );
lv_obj_set_y( ui_SettingsKeyboardText, 145 );
lv_obj_set_align( ui_SettingsKeyboardText, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_SettingsKeyboardText, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_SettingsKeyboardText, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE );    /// Flags

lv_obj_add_event_cb(ui_SettingsBackToHome, ui_event_SettingsBackToHome, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsHeaderPanel, ui_event_SettingsHeaderPanel, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiPasswordTextInput, ui_event_WifiPasswordTextInput, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiScanButton, ui_event_WifiScanButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiSaveButton, ui_event_WifiSaveButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_TestWifiSettingsButton, ui_event_TestWifiSettingsButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ComputerAuthUsername, ui_event_ComputerAuthUsername, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ComputerAuthPassword, ui_event_ComputerAuthPassword, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ComputerSaveButton, ui_event_ComputerSaveButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ScreenBrightnessArk, ui_event_ScreenBrightnessArk, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsPanel, ui_event_SettingsPanel, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_SettingsView, ui_event_SettingsView, LV_EVENT_ALL, NULL);

}

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Home_screen_init();
ui_SettingsView_screen_init();
lv_disp_load_scr( ui_Home);
}
