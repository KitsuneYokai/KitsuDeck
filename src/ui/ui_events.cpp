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

#include "../utils/macros.h"
#include "../main.h"

void initKitsuDeckMacros(lv_event_t *e)
{
	loadKitsuDeckMacros();
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

void DeckNavSliderReleased(lv_event_t *e)
{
	loadKitsuDeckMacros();
	lv_obj_set_style_opa(ui_PageChangePanel, 0, 0);
}

void DeckNavSliderValueChange(lv_event_t *e)
{
	lv_obj_set_style_opa(ui_PageChangePanel, 255, 0);

	// get the value of the slider
	String value = String(lv_slider_get_value(ui_DeckNavSlider) + 1);
	// set the value to the label
	lv_label_set_text(ui_PageText, value.c_str());
}
