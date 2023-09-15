#ifndef _SETTINGS_H
#define _SETTINGS_H
#define SETTINGS_FILE "/settings.json"

#include <Arduino.h>

void createSettings();
bool checkSettingsBool();
bool checkSettingsWifiBool();
String validateSettingsJson();
String getSettings(String key);
String setSettings(String key, String value);
void initSettings();

#endif
