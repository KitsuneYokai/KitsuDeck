#include "Arduino.h"
// #include "wifiUtils.h"
#include "WiFi.h"
#include "../ui/ui.h"

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

bool testWifiConnection(String ssid, String password)
{
    WiFi.begin(ssid.c_str(), password.c_str());
    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i < 10)
    {
        delay(500);
        i++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.disconnect();
        return true;
    }
    else
    {
        return false;
    }
}