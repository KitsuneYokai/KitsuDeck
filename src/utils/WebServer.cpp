#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include "SD.h"
#include "WebServer.h"
#include "Settings.h"
#include "utils/wifiUtils.h"

#include "utils/ScreenMessages.h"

AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");

void handleWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    // Handle WebSocket message here
    if (type == WS_EVT_CONNECT)
    {
        // if client connects to the websocket send hello message as a test
        client->text("Hello Client " + String(client->id()));
    }
}

void startWebServer(void *parameter)
{
    vTaskDelay(500);
    if (checkSettingsWifiBool())
    {
        Serial.println("Starting Web/WebSocket server");
        // connect to wifi
        WiFi.begin(getSettings("wifi_ssid").c_str(), getSettings("wifi_password").c_str());
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/plain", "Hello World"); });

        // Setup WebSocket server
        webSocket.onEvent(handleWebSocketMessage);
        server.addHandler(&webSocket);

        server.begin();

        while (true)
        {
            // Wait for incoming client requests and WebSocket messages
            vTaskDelay(500);
            webSocket.cleanupClients(); // Cleanup disconnected clients
        }
    }
    else
    {
        vTaskDelete(NULL);
    }
}
