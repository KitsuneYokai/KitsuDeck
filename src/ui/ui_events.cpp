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
#include "../utils/Timers/clock.h"

#include "../utils/macros.h"
#include "../main.h"

void initKitsudeck(lv_event_t * e)
{
	// load the macros
	loadKitsuDeckMacros();
	// init the settings page values
	initSettings();
	// start the clock timer
	initClockTimer();
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

void saveClockUtcSettings(lv_event_t * e)
{
	char selected_utc[7];
	lv_roller_get_selected_str(ui_ClockTimezoneRoller, selected_utc, 100);
	printf("Selected UTC: %s\n", selected_utc);

	// save the utc to the settings
	setSettings("utc", selected_utc);
	String utc = "Selected Timezone: " + String(selected_utc);

	// set the selected label to the current utc
	lv_label_set_text(ui_ClockUtcSelected, utc.c_str());
	// update the clock
	stopSNTP();
    initSNTP();
    xTaskCreate(wait_for_sntp_sync, "SNTP_Task", 4096, NULL, 5, NULL);
}
