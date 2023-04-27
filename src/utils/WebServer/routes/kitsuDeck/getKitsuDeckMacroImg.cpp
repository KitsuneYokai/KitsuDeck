#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "kitsuDeck.h"
#include "../../../Settings.h"
#include "../../../Database/Sqlite.h"

void handleGetKitsuDeckMacroImg(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    // TODO: Convert this to use the select all function, since it kinda works better
    static char *requestData = NULL;
    static size_t requestDataSize = 0;
    if (index == 0)
    {
        // Free the memory allocated for any previous request data
        if (requestData != NULL)
        {
            free(requestData);
            requestData = NULL;
        }

        // Initialize a new buffer for storing the request body data
        requestDataSize = total;
        requestData = (char *)malloc(requestDataSize + 1); // add 1 for null-terminator
        if (!requestData)
        {
            // If there was an error allocating memory for the request data, send a 500 Internal Server Error response
            request->send(500, "text/plain", "Internal Server Error");
            return;
        }
        requestData[0] = '\0';
    }
    // Append the incoming data to the buffer
    strncat(requestData, (const char *)data, len);

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
            DynamicJsonDocument macro = selectOne(("SELECT picture FROM makros WHERE " + id_condition).c_str());

            // If the macro is found, send a 200 OK response with the macro data
            if (macro != "No rows returned")
            {
                // Get the base64-encoded image data from the macro
                String imageBase64 = macro["picture"].as<String>();

                // Send the image data in chunks of 1KB
                const int chunkSize = 1024;
                const int numChunks = (imageBase64.length() + chunkSize - 1) / chunkSize;
                for (int i = 0; i < numChunks; i++)
                {
                    int start = i * chunkSize;
                    int end = start + chunkSize;
                    String chunk = imageBase64.substring(start, end);
                    request->sendChunked("image/jpeg", [&](uint8_t *buffer, size_t maxLen, size_t index) -> size_t
                                         {
                                            size_t chunkLen = chunk.length() - index;
                                            if (chunkLen > maxLen) {
                                                chunkLen = maxLen;
                                            }
                                            memcpy(buffer, (const uint8_t *)chunk.c_str() + index, chunkLen);
                                            return chunkLen; });
                }
            }
            // If the macro is not found, send a 404 Not Found response
            else
            {
                request->send(404);
            }
        }

        // Free the memory allocated for the request data
        free(requestData);
        requestData = NULL;
        requestDataSize = 0;
    }
}