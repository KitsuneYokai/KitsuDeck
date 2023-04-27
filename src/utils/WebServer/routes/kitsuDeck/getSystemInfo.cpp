#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "Arduino.h"

void handleGetKitsuDeckSystemInfo(AsyncWebServerRequest *request)
{
    char Ser[1024];
    DynamicJsonDocument doc(1024);
    doc["heap"] = ESP.getFreeHeap();
    doc["psram"] = ESP.getFreePsram();

    serializeJson(doc, Ser);
    // Send the system info
    request->send(200, "application/json", Ser);
}