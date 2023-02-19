#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "wifiUtils.h"
#include "WebServer.h"
#include "Settings.h"

#define SERVER_PORT 80
#define ROOT_ENDPOINT "/"

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

// Handle HTTP GET request for /
void handleRootRequest(AsyncWebServerRequest *request)
{
    // make a json
    StaticJsonDocument<200> doc;
    doc["status"] = true;
    doc["message"] = "Hi, Im KitsuDeck, nice to meet you! Im a Makro keyboard thats connected to some pc in your Network, and i can do some other cool stuff, so please dont delete me from your Network, because someone in your network is using me!";
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

// Start the web server and WebSocket server
void startWebServer(void *parameter)
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    if (checkSettingsWifiBool())
    {
        Serial.println("Starting Web/WebSocket server");

        // Connect to WiFi
        connectToWifi(getSettings("wifi_ssid"), getSettings("wifi_password"));

        // Setup HTTP GET handler for /
        server.on(ROOT_ENDPOINT, HTTP_GET, handleRootRequest);

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