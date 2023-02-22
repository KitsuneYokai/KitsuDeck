#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "Auth.h"
#include "../../../Settings.h"


void handleKitsuDeckAuthRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
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
        StaticJsonDocument<200> response;
        response["status"] = false;

        DeserializationError error = deserializeJson(doc, requestData);
        if (error)
        {
            // If there was an error parsing the JSON data, send a 400 Bad Request error response
            request->send(400, "text/plain", "Bad Request");
        }
        else
        {
            // Extract the username and password from the JSON data
            String username = doc["username"];
            String password = doc["password"];
            // Check if the username and password are valid
            if (getSettings("computer_user") == username && getSettings("computer_password") == password)
            {
                // If the user is valid, send a 200 OK response with the authentication status
                response["status"] = true;
                request->send(200, "application/json", response.as<String>());
            }
            else
            {
                // If the user is invalid, send a 200 OK response with the authentication status
                request->send(200, "application/json", response.as<String>());
            }
        }
    }
}