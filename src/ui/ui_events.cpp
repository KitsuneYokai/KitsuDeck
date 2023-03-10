// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: KitsuDeck

#include "ui.h"
#include "../utils/wifiUtils.h"
#include "../utils/settings.h"
#include "../utils/Screen.h"
#include "WiFi.h"

void initHome(lv_event_t *e)
{
	// Your code here
}

void initSettings(lv_event_t *e)
{
	// set the values of the wifi settings
	String wifiSsid = getSettings("wifi_ssid");
	String wifiPassword = getSettings("wifi_password");
	lv_roller_set_options(ui_WifiSsidRoller, wifiSsid.c_str(), LV_ANIM_ON);
	lv_textarea_set_text(ui_WifiPasswordTextInput, wifiPassword.c_str());

	// set the values of the computer settings
	String computerUser = getSettings("computer_user");
	String computerPassword = getSettings("computer_password");
	lv_textarea_set_text(ui_ComputerAuthUsername, computerUser.c_str());
	lv_textarea_set_text(ui_ComputerAuthPassword, computerPassword.c_str());

	// SettingsBrightness ark init
	String value = getSettings("brightness");
	// convert the value 255 to be maximum 100
	value = String((value.toInt() * 100) / 255);
	lv_arc_set_value(ui_ScreenBrightnessArk, value.toInt());
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

void SaveComputerSettings(lv_event_t *e)
{
	String username = lv_textarea_get_text(ui_ComputerAuthUsername);
	String password = lv_textarea_get_text(ui_ComputerAuthPassword);

	setSettings("computer_user", username);
	setSettings("computer_password", password);
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
