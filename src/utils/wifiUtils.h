#ifndef _WIFI_UTILS_H
#define _WIFI_UTILS_H
#include <Arduino.h>

String getNetworks();
String testWifiConnection(String ssid, String password);
String getKitsuDeckHostname();
bool connectToWifi(String ssid, String password);
bool disconnectFromWifi();
#endif