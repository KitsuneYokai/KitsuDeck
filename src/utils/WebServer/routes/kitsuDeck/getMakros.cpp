#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "../../../Settings.h"
#include "../../../Database/Sqlite.h"

void handleKitsuDeckGetMakrosRequest(AsyncWebServerRequest *request)
{
    char *buffer = getMakrosFromDatabase();
    if (buffer == nullptr)
    {
        request->send(500, "text/plain", "Error fetching data from database.");
    }
    else
    {
        request->send(200, "application/json", buffer);
        free(buffer);
    }
}