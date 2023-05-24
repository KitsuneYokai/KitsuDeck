#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "../wifiUtils.h"
#include "../Settings.h"
#include "WebServer.h"

#include "../wifiUtils.h"
// define the web server and websocket server objects
AsyncWebServer server(SERVER_PORT);
AsyncWebSocket webSocket(WEBSOCKET_ENDPOINT);

void handleWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    // Echo the received message back to the client
    // Send a text if the user connects
    if (type == WS_EVT_CONNECT)
    {
        client->text("Hello from KitsuDeck!");
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        // Client disconnected, perform necessary cleanup
        // For example, remove the client from any data structures
        // and release any associated resources
        // ...

        return; // Exit the function to prevent further processing
    }

    // Check if the client is still connected before sending a message
    if (client->status() == WS_CONNECTED)
    {
        client->text((char *)data, len);
    }
}
// Handle HTTP GET request for /
void handleRootRequest(AsyncWebServerRequest *request)
{
    // make a json
    String ip = WiFi.localIP().toString();
    String hostname = getKitsuDeckHostname();
    StaticJsonDocument<200> doc;
    doc["message"] = "Hi, Im KitsuDeck, nice to meet you!\nIm a Macro keyboard that is connected to some pc in your Network, so please dont delete me from your Network, because someone in your network is using me!\nHere is a link to my github repository: https://github.com/KitsuneYokai/KitsuDeck";
    doc["status"] = true;
    doc["ip"] = ip;
    doc["hostname"] = hostname;
    doc["version"] = "0.0.1";
    // if any auth variable in the settings is set, let it be only the username, set the json protected value to true
    if (getSettings("auth_pin") != "")
    {
        doc["protected"] = true;
    }
    else
    {
        doc["protected"] = false;
    }

    request->send(200, "text/plain", doc.as<String>());
}
// Handle HTTP POST request for /auth
void handleAuthRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
    String requestData;
    if (index == 0)
    {
        requestData = "";
    }
    for (size_t i = 0; i < len; i++)
    {
        requestData += (char)data[i];
    }

    if (index + len == total)
    {
        StaticJsonDocument<200> doc;
        StaticJsonDocument<200> response;
        response["status"] = false;

        DeserializationError error = deserializeJson(doc, requestData);
        if (error)
        {
            request->send(400, "text/plain", "Bad Request");
        }
        else
        {
            String pin = doc["auth_pin"];
            if (getSettings("auth_pin") == pin)
            {
                response["status"] = true;
                request->send(200, "application/json", response.as<String>());
            }
            else
            {
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
        bool wifi_connect = connectToWifi(getSettings("wifi_ssid"), getSettings("wifi_password"));

        if (!wifi_connect)
        {
            Serial.println("Failed to connect to WiFi");
            vTaskDelete(NULL);
        }

        // Setup HTTP GET handler for /
        server.on(ROOT_ENDPOINT, HTTP_GET, handleRootRequest);
        // Setup auth endpoint
        server.on(
            Auth_ENDPOINT, HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, handleAuthRequest);
        // Setup 404
        server.onNotFound([](AsyncWebServerRequest *request)
                          { request->send(404, "text/plain", "What are you looking for?. Anyways... I couldn't find what you are looking for, 404"); });

        // Setup WebSocket server
        webSocket.onEvent(handleWebSocketMessage);
        server.addHandler(&webSocket);
        server.begin();

        // Wait for incoming client requests and WebSocket messages
        while (true)
        {
            vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for 1 second
            webSocket.cleanupClients();            // Cleanup disconnected clients
        }

        // Cleanup and release resources before deleting the task (this part is not reached in the current implementation)
        server.end();
        webSocket.closeAll();
    }
    else
    {
        vTaskDelete(NULL);
    }
}