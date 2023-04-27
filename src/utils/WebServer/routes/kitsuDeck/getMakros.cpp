#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "../../../Settings.h"
#include "../../../Database/Sqlite.h"

void handleKitsuDeckGetMakrosRequest(AsyncWebServerRequest *request)
{
    DynamicJsonDocument makro = selectAll("SELECT id, name, description, invoked FROM makros");
    String output;
    serializeJson(makro, output);

    request->send(200, "application/json; charset=utf-8", output);
}