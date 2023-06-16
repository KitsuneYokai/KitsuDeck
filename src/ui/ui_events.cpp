// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: KitsuDeck

#include "ui.h"
#include "../utils/wifiUtils.h"
#include "../utils/settings.h"
#include "../utils/Screen.h"
#include "WiFi.h"
#include "../utils/Database/Sqlite.h"
#include "../main.h"

void initHome(lv_event_t *e)
{
	// clear all items from ui_DeckCol
	lv_obj_clean(ui_DeckCol);

	// get the first 20 macros from the database and display them, order the query by layout_position and add a offset
	String offset = String(0);
	String macro_quarry = "SELECT * FROM macros WHERE NOT layout_position=0 ORDER BY layout_position ASC LIMIT 20 OFFSET " + offset;
	DynamicJsonDocument macros = selectAll(macro_quarry.c_str());

	Serial.println(macros.as<String>());
	// fill macros into ui_DeckCol, by getting the layout_position value from macros, and setting the macros at the right position
	for (int i = 0; i < 20; i++)
	{
		bool macro_exists = false;
		// go through the macros array and get the layout_position value
		for (int j = 0; j < macros.size(); j++)
		{
			int layout_position = macros[j]["layout_position"].as<int>();
			if (layout_position == i + 1)
			{
				// set the macro at the right position
				Serial.println("setting macro at position " + String(i + 1));
				// create a new macro button
				lv_obj_t *macro = lv_imgbtn_create(ui_DeckCol);
				lv_obj_set_size(macro, 100, 100);
				// set the image of the macro button
				String image = macros[j]["image"];
				if (image == "null")
				{
					Serial.println("image is null, setting default image");
					lv_img_set_src(macro, &ui_img_macro_icon_png);
				}
				else
				{
					String macro_image_quary = "SELECT name FROM macro_images WHERE id = " + image;
					DynamicJsonDocument macro_image_path = selectOne(macro_image_quary.c_str());
					Serial.println(macro_image_path.as<String>());
					String imagePath = "S:/images/macro_images/" + macro_image_path["name"].as<String>();
					lv_img_set_src(macro, imagePath.c_str());
				}
				// TODO: btn click event
				macro_exists = true;
				break;
			}
		}
		if (!macro_exists)
		{
			// creating an empty canvas with the same size as the macro (100x100) to keep the layout
			lv_obj_t *macro_spacer = lv_canvas_create(ui_DeckCol);
			lv_obj_set_size(macro_spacer, 100, 100);
			Serial.println("setting empty macro at position " + String(i + 1));
		}
	}
}

void initSettings(lv_event_t *e)
{
	// set the values of the wifi settings
	String wifiSsid = getSettings("wifi_ssid");
	String wifiPassword = getSettings("wifi_password");
	lv_roller_set_options(ui_WifiSsidRoller, wifiSsid.c_str(), LV_ANIM_ON);
	lv_textarea_set_text(ui_WifiPasswordTextInput, wifiPassword.c_str());

	// set the values of the Auth Settings
	String pin = getSettings("auth_pin");
	if (pin != "")
	{
		lv_label_set_text(ui_AuthStatus, "Status: Secured");
		lv_obj_clear_flag(ui_ComputerAuthPinNew, LV_OBJ_FLAG_HIDDEN);
	}
	else
	{
		lv_label_set_text(ui_AuthStatus, "Status: Not Secured");
		lv_obj_add_flag(ui_ComputerAuthPinNew, LV_OBJ_FLAG_HIDDEN);
	}

	// SettingsBrightness ark init
	String value = getSettings("brightness");
	value = String((value.toInt() * 100) / 255);
	lv_arc_set_value(ui_ScreenBrightnessArk, value.toInt());

	// SettingsInformation init
	lv_label_set_text(ui_KitsuDeckVersion, "Version: " VERSION);
	// set ram
	String ram = String(ESP.getFreeHeap());
	lv_label_set_text(ui_RamValue, ram.c_str());
	// set psram
	String psram = String(ESP.getFreePsram());
	lv_label_set_text(ui_PsramValue, psram.c_str());
}

void ScanWifiSsid(lv_event_t *e)
{
	String WifiNetworks = getNetworks();
	lv_roller_set_options(ui_WifiSsidRoller, WifiNetworks.c_str(), LV_ANIM_ON);
	if (checkSettingsWifiBool())
	{
		testWifiConnection(getSettings("wifi_ssid"), getSettings("wifi_password"));
	}
}

void SaveWifiSettings(lv_event_t *e)
{
	// get values from ui_WifiPasswordTextInput and ui_WifiSsidRoller
	String password = lv_textarea_get_text(ui_WifiPasswordTextInput);
	// get the ssid form the roller
	char ssid[100];
	lv_roller_get_selected_str(ui_WifiSsidRoller, ssid, 100);
	String finalSsid = String(ssid);
	String wifiTest = testWifiConnection(finalSsid, password);
	if (wifiTest != "error")
	{
		lv_label_set_text(ui_WifiTestResultLabel, wifiTest.c_str());
		setSettings("wifi_ssid", finalSsid);
		setSettings("wifi_password", password);
	}
}

void TestWifiSettings(lv_event_t *e)
{
	// get values ssid and password from settings
	String password = getSettings("wifi_password");
	String ssid = getSettings("wifi_ssid");
	String testResult = testWifiConnection(ssid, password);

	char testResultChar[testResult.length() + 1];
	testResult.toCharArray(testResultChar, testResult.length() + 1);
	// set the test result to the ui_WifiTestResultLabel
	if (testResult != "error")
	{
		lv_label_set_text(ui_WifiTestResultLabel, testResultChar);
	}
	else
	{
		lv_label_set_text(ui_WifiTestResultLabel, "Not Connected");
	}
}

void SaveComputerAuthSettings(lv_event_t *e)
{
	String currentPin = getSettings("auth_pin");
	String pin = lv_textarea_get_text(ui_ComputerAuthPin);
	String newPin = lv_textarea_get_text(ui_ComputerAuthPinNew);
	if (currentPin != "")
	{
		if (pin == currentPin)
		{
			setSettings("auth_pin", newPin);
			lv_label_set_text(ui_AuthStatus, "Status: New Pin Set");
			if (newPin == "")
			{
				lv_obj_add_flag(ui_ComputerAuthPinNew, LV_OBJ_FLAG_HIDDEN);
			}
			else
			{
				lv_obj_clear_flag(ui_ComputerAuthPinNew, LV_OBJ_FLAG_HIDDEN);
			}
			// TODO: restart the webserver task
		}
		else
		{
			lv_label_set_text(ui_AuthStatus, "Status: Wrong Pin");
		}
	}
	else
	{
		setSettings("auth_pin", pin);
		lv_label_set_text(ui_AuthStatus, "Status: New Pin Set");
		if (pin == "")
		{
			lv_obj_add_flag(ui_ComputerAuthPinNew, LV_OBJ_FLAG_HIDDEN);
		}
		else
		{
			lv_obj_clear_flag(ui_ComputerAuthPinNew, LV_OBJ_FLAG_HIDDEN);
		}
	}
	lv_textarea_set_text(ui_ComputerAuthPinNew, "");
	lv_textarea_set_text(ui_ComputerAuthPin, "");
}

void setSettingsBrightnessArkValue(lv_event_t *e)
{

	String value = String(lv_arc_get_value(ui_ScreenBrightnessArk));
	// convert the value to be maximum 255 and minimum 10
	value = String((value.toInt() * 255) / 100);
	if (value.toInt() < 10)
		value = "10";
	setLCDBrightness(value.toInt());
}

void saveSettingsBrightnessArkValue(lv_event_t *e)
{
	String value = String(lv_arc_get_value(ui_ScreenBrightnessArk));
	// convert the value to be maximum 255 and minimum 10
	value = String((value.toInt() * 255) / 100);
	if (value.toInt() < 10)
		value = "10";
	setSettings("brightness", value);
}
