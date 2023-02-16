#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "WebServer.h"
#include "Settings.h"
#include "utils/wifiUtils.h"

#include "utils/ScreenMessages.h"

AsyncWebServer server(80);
void startWebServer(void *parameter)
{
    // initialize WiFi
    // check if the settings file has a ssid and password
    String ssid = getSettings("wifi_ssid");
    String password = getSettings("wifi_password");

    // TODO: make better :P
    if (ssid != "" || password != "")
    {
        bool wifiCheck = connectToWifi(ssid.c_str(), password.c_str());
        if (!wifiCheck)
        {
            errorWiFi();
        }
    }

    server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello World"); });

    server.begin();

    while (1)
    {
        // Wait for incoming client requests
        delay(1000);
    }
}