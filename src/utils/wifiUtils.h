#ifndef _WIFI_UTILS_H
#define _WIFI_UTILS_H
#include <Arduino.h>

String getNetworks();
bool testWifiConnection(String ssid, String password);
#endif