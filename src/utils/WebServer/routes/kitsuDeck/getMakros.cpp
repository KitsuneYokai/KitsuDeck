#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "../../../Settings.h"
#include "../../../Database/Sqlite.h"

void handleKitsuDeckGetMakrosRequest(AsyncWebServerRequest *request)
{
    String makros = selectAll("SELECT id,name,description,invoked FROM makros");
    // If the macro is found, send a 200 OK response with the macro data
    if (makros != "No rows returned")
    {
        request->send(200, "application/json", makros.c_str());
    }
    else
    {
        request->send(200, "application/json", makros.c_str());
    }
}