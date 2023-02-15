#include "Arduino.h"
// #include "wifiUtils.h"
#include "WiFi.h"
#include "../ui/ui.h"

String getKitsuDeckHostname()
{
    uint64_t chipid = ESP.getEfuseMac();
    char hostname[64] = "KitsuDeck-";
    sprintf(hostname + 10, "%04X%08X", (uint16_t)(chipid >> 32), (uint32_t)chipid);
    return hostname;
}

// TODO: make this a task that gets invoked when entering the settings screen, so its non blocking
String getNetworks()
{
    String networks = "";
    int n = WiFi.scanNetworks();
    delay(6000);
    if (n == 0)
    {
        networks = "No networks found";
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            networks += WiFi.SSID(i);
            if (i < n - 1)
            {
                networks += "\n";
            }
        }
    }
    return networks;
}

String testWifiConnection(String ssid, String password)
{
    int i = 0;
    String hostname = getKitsuDeckHostname();
    WiFi.setHostname(hostname.c_str());
    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED && i < 10)
    {
        delay(500);
        i++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.disconnect();
        // return the IP address of the ESP32
        return WiFi.localIP().toString();
    }
    else
    {
        return "error";
    }
}

bool connectToWifi(String ssid, String password)
{
    int i = 0;
    String hostname = getKitsuDeckHostname();
    WiFi.setHostname(hostname.c_str());
    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED && i < 10)
    {
        delay(500);
        i++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool disconnectFromWifi()
{
    WiFi.disconnect();
    return true;
}