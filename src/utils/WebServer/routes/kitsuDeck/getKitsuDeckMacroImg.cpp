#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "../../../Settings.h"
#include "../../../Database/Sqlite.h"

void handleGetKitsuDeckMacroImg(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    String requestData;
    if (index == 0)
    {
        // Initialize a new buffer for storing the request body data
        requestData = "";
    }
    // Append the incoming data to the buffer
    for (size_t i = 0; i < len; i++)
    {
        requestData += (char)data[i];
    }

    if (index + len == total)
    {
        // If all of the request data has been received, parse the JSON data
        StaticJsonDocument<200> doc;

        DeserializationError error = deserializeJson(doc, requestData);
        if (error)
        {
            // If there was an error parsing the JSON data, send a 400 Bad Request error response
            request->send(400, "text/plain", "Bad Request");
        }
        else
        {
            // Extract the username and password from the JSON data
            // String username = doc["username"];
            // String password = doc["password"];
            // TODO: check if the user is valid ... u know the drill by now :)      just skiping so i can get it working faster

            // get the requested id from the post data
            String id = doc["id"].as<String>();

            std::string id_condition = "id = " + std::string(id.c_str());
            String macro = selectOne(("SELECT picture FROM makros WHERE " + id_condition).c_str());

            // If the macro is found, send a 200 OK response with the macro data
            if (macro != "No rows returned")
            {
                request->send(200, "application/json", macro.c_str());
            }
            // If the macro is not found, send a 404 Not Found response
            else
            {
                request->send(404);
            }
        }
    }
}
