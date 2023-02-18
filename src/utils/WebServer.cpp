#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "wifiUtils.h"
#include "WebServer.h"
#include "Settings.h"

#define SERVER_PORT 80
#define HELLO_ENDPOINT "/hello"

AsyncWebServer server(SERVER_PORT);
AsyncWebSocket webSocket("/ws");

// Handle WebSocket messages
void handleWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        client->text("Hello Client " + String(client->id()));
    }
}

// Start the web server and WebSocket server
void startWebServer(void *parameter)
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    if (checkSettingsWifiBool())
    {
        Serial.println("Starting Web/WebSocket server");

        // Connect to WiFi
        connectToWifi(getSettings("wifi_ssid"), getSettings("wifi_password"));

        // Handle HTTP GET request for /hello
        server.on(HELLO_ENDPOINT, HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/plain", "Hello World"); });

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