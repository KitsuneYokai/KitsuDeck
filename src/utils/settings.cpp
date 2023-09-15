#include "settings.h"
#include "ScreenMessages.h"

#include "Arduino.h"
#include "SD.h"
#include <ArduinoJson.h>

#include "../ui/ui.h"
#include "../main.h"

void createSettings()
{
    File file = SD.open(SETTINGS_FILE);
    if (file)
    {
        // delete the file
        SD.remove(SETTINGS_FILE);
    }
    // create the file and write the default settings using ArduinoJson
    file = SD.open(SETTINGS_FILE, FILE_WRITE);
    if (file)
    {
        StaticJsonDocument<1024> doc;
        doc["brightness"] = 100;
        doc["wifi_ssid"] = "";
        doc["wifi_password"] = "";
        doc["auth_pin"] = "";
        doc["utc"] = "00:00";
        serializeJson(doc, file);
        file.close();
    }
}

bool checkSettingsWifiBool()
{
    if (SD.exists(SETTINGS_FILE))
    {
        // check if the wifi_ssid and wifi_password are set
        if (getSettings("wifi_ssid") != "" && getSettings("wifi_password") != "")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
/* Settings Functions */
// settings file variable

bool checkSettingsBool()
{
    if (SD.exists(SETTINGS_FILE))
    {
        return true;
    }
    else
    {
        return false;
    }
}

String validateSettingsJson()
{
    File file = SD.open(SETTINGS_FILE);
    if (file)
    {
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, file);
        if (error)
        {
            return "false";
        }
        else
        {
            return "true";
        }
    }
    else
    {
        return "false";
    }
}

String getSettings(String setting)
{
    File file = SD.open(SETTINGS_FILE);
    if (file)
    {
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, file);
        if (error)
        {
            errorSettings();
        }
        else
        {
            return doc[setting];
        }
    }
    return "false";
}

String setSettings(String setting, String value)
{
    File file = SD.open(SETTINGS_FILE);
    if (file)
    {
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, file);
        if (error)
        {
            errorSettings();
        }
        else
        {
            doc[setting] = value;
            file.close();
            file = SD.open(SETTINGS_FILE, FILE_WRITE);
            if (file)
            {
                serializeJson(doc, file);
                file.close();
                return "true";
            }
            else
            {
                return "false";
            }
        }
    }
    return "false";
}

// function to init the KitsuDecks settings values ark sliders and rollers
void initSettings()
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

	// TODO: SettingsInformation init
    String utc = getSettings("utc");
    String utcString = "Selected Timezone: " + utc;
    lv_label_set_text(ui_ClockUtcSelected, utcString.c_str());

    // set ram
	String ram = String(ESP.getFreeHeap());
	lv_label_set_text(ui_RamValue, ram.c_str());
	// set psram
	String psram = String(ESP.getFreePsram());
	lv_label_set_text(ui_PsramValue, psram.c_str());
}