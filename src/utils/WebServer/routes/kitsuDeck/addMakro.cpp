#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "../../../Settings.h"
#include "../../../Database/Sqlite.h"

// Define the maximum size of the JSON document to handle (in bytes)
#define MAX_JSON_SIZE 8192

void cleanup(uint8_t *&psram_buffer, DynamicJsonDocument &jsonBuffer)
{
    free(psram_buffer);
    psram_buffer = nullptr;
    jsonBuffer.clear();
}

void handleKitsuDeckAddMakroRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    static uint8_t *psram_buffer = nullptr;
    static size_t psram_buffer_size = 0;
    static DynamicJsonDocument jsonBuffer(1024);

    if (index == 0)
    {
        // If this is the first chunk of data, allocate a PSRAM buffer for storing the entire request body
        psram_buffer_size = total;
        psram_buffer = (uint8_t *)ps_malloc(psram_buffer_size);
        if (psram_buffer == nullptr)
        {
            request->send(500, "text/plain", "Failed to allocate PSRAM buffer");
            return;
        }
    }

    // Copy the incoming data into the PSRAM buffer
    memcpy(psram_buffer + index, data, len);

    if (index + len == total)
    {
        // If all of the request data has been received, parse the JSON data
        DeserializationError error = deserializeJson(jsonBuffer, psram_buffer, total);
        if (error)
        {
            // If there was an error parsing the JSON data, send a 400 Bad Request error response
            request->send(400, "text/plain", "DeserializationError");
            cleanup(psram_buffer, jsonBuffer);
            return;
        }

        // TODO: check if the user needs to be authenticated

        // Extract data from the JSON document
        const String name = jsonBuffer["name"].as<String>();
        const String key = jsonBuffer["key"].as<String>();
        const String description = jsonBuffer["description"].as<String>();
        const String type = jsonBuffer["type"].as<String>();
        const String picture = jsonBuffer["picture"].as<String>();

        // Make mysql query
        String query = "INSERT INTO `makros` (`name`, `key`, `description`, `type`, `picture`) VALUES ('" + name + "', '" + key + "', '" + description + "', '" + type + "', '" + picture + "')";
        // Execute query
        int rc = db_exec(query.c_str());
        // check if the query was executed successfully
        // Send a 200 OK response with the authentication status
        if (rc == SQLITE_DONE)
        {
            request->send(200, "application/json", "{\"status\":true}");
        }
        else
        {
            request->send(200, "application/json", "{\"status\":false}");
        }
        // Free the PSRAM buffer and clear the JSON buffer
        cleanup(psram_buffer, jsonBuffer);
    }
}