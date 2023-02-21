#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "wifiUtils.h"
#include "WebServer.h"
#include "Settings.h"

// define the server port
#define SERVER_PORT 80
// define the api endpoints
#define ROOT_ENDPOINT "/"
#define KITSUDECK_AUTH "/kitsuDeck/auth"

// define the webserver and websocket server objects
AsyncWebServer server(SERVER_PORT);
AsyncWebSocket webSocket("/ws");

// TODO: Split this file into multiple files for better readability/structure
// Handle WebSocket messages
void handleWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        // client has connected
    }
    else if (type == WS_EVT_DATA)
    {
        // received data from client
        String message = String((char *)data);
        if (message.indexOf("ping") != -1)
        {
            // send a ping back to the client
            client->text("pong");
        }
    }
}
// Handle HTTP GET request for /
void handleRootRequest(AsyncWebServerRequest *request)
{
    // make a json
    StaticJsonDocument<200> doc;
    doc["message"] = "Hi, Im KitsuDeck, nice to meet you! Im a Makro keyboard that is connected to some pc in your Network, so please dont delete me from your Network, because someone in your network is using me! :D here is a link to my github repository: https://github.com/KitsuneYokai/KitsuDeck";
    doc["status"] = true;
    doc["version"] = "0.0.1";
    // if any auth variable in the settings is set, let it be only the username, set the json protected value to true
    if (getSettings("computer_user") != "" || getSettings("computer_password") != "")
    {
        doc["protected"] = true;
    }
    else
    {
        doc["protected"] = false;
    }

    request->send(200, "text/plain", doc.as<String>());
}

// Handle HTTP POST request for /kitsuDeck/auth
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

// Start the web server and WebSocket server
void startWebServer(void *parameter)
{
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    if (checkSettingsWifiBool())
    {
        Serial.println("Starting Web/WebSocket server");

        // Connect to WiFi
        connectToWifi(getSettings("wifi_ssid"), getSettings("wifi_password"));

        // Setup HTTP GET handler for /
        server.on(ROOT_ENDPOINT, HTTP_GET, handleRootRequest);
        server.on(
            KITSUDECK_AUTH, HTTP_POST, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "You've made a POST request"); },
            NULL, handleKitsuDeckAuthRequest);
        // 404
        server.onNotFound([](AsyncWebServerRequest *request)
                          { request->send(404, "text/plain", "What yre you looking for ?.?,\nAnyways ... i couldn't find what you are looking for, 404"); });
        // Setup WebSocket server
        webSocket.onEvent(handleWebSocketMessage);
        server.addHandler(&webSocket);

        server.begin();

        // Wait for incoming client requests and WebSocket messages
        while (true)
        {
            vTaskDelay(1000);           // Wait for 1 second
            webSocket.cleanupClients(); // Cleanup disconnected clients
        }
    }
    else
    {
        vTaskDelete(NULL);
    }
}