#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "../../../Settings.h"
#include "../../../Database/Sqlite.h"

// Define the maximum size of the JSON document to handle (in bytes)
#define MAX_JSON_SIZE 8192

// create a buffer for storing the request body data
uint8_t *psram_buffer = NULL;
size_t psram_buffer_size = 0;

// create and a buffer for storing the request body data
void handleKitsuDeckAddMakroRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    if (index == 0)
    {
        // If this is the first chunk of data, allocate a PSRAM buffer for storing the entire request body
        if (psram_buffer != NULL)
        {
            free(psram_buffer);
            psram_buffer_size = 0;
        }
        psram_buffer = (uint8_t *)ps_malloc(len);
        psram_buffer_size = len;
    }
    else
    {
        // If this is not the first chunk of data, resize the PSRAM buffer if necessary
        if (index + len > psram_buffer_size)
        {
            uint8_t *new_buffer = (uint8_t *)ps_realloc(psram_buffer, index + len);
            if (new_buffer == NULL)
            {
                request->send(500, "text/plain", "Failed to allocate PSRAM buffer");
                return;
            }
            psram_buffer = new_buffer;
            psram_buffer_size = index + len;
        }
    }

    // Copy the incoming data into the PSRAM buffer
    memcpy(psram_buffer + index, data, len);

    if (index + len == total)
    {
        // If all of the request data has been received, parse the JSON data
        StaticJsonDocument<MAX_JSON_SIZE> doc;

        DeserializationError error = deserializeJson(doc, psram_buffer, total);
        if (error)
        {
            // If there was an error parsing the JSON data, send a 400 Bad Request error response
            request->send(400, "text/plain", "DeserializationError");
        }
        else
        {
            // TODO: check if the user needs to be authenticated

            // Extract data from the JSON document
            String name = doc["name"];
            String key = doc["key"];
            String description = doc["description"];
            String type = doc["type"];
            String picture = doc["picture"];
            // make mysql query
            String query = "INSERT INTO `makros` (`name`, `key`, `description`, `type`, `picture`) VALUES ('" + name + "', '" + key + "', '" + description + "', '" + type + "', '" + picture + "')";
            // execute query
            db_exec(query.c_str());
            // send a 200 OK response with the authentication status
            request->send(200, "application/json", doc.as<String>());
        }

        // Free the PSRAM buffer
        free(psram_buffer);
        psram_buffer = NULL;
        psram_buffer_size = 0;
    }
}