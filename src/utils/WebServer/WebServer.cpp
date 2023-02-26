#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "../wifiUtils.h"
#include "../Settings.h"
#include "WebServer.h"

// import the routes from the routes folder
#include "routes/kitsuDeck/kitsuDeck.h"

// define the webserver and websocket server objects
AsyncWebServer server(SERVER_PORT);
AsyncWebSocket webSocket(WEBSOCKET_ENDPOINT);

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
        // Setup HTTP POST handler for /kitsuDeck/auth
        server.on(
            KITSUDECK_AUTH, HTTP_POST, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "You've made a POST request"); },
            NULL, handleKitsuDeckAuthRequest);
        // Setup HTTP POST handler for /kitsuDeck/AddMakro
        server.on(
            KITSUDECK_ADD_MAKRO, HTTP_POST, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "You've made a POST request"); },
            NULL, handleKitsuDeckAddMakroRequest);
        // Setup HTTP GET handler for /kitsuDeck/getMakros
        server.on(KITSUDECK_GET_MAKROS, HTTP_GET, handleKitsuDeckGetMakrosRequest);
        // Setup HTTP POST handler for /kitsuDeck/getMakroImg
        server.on(
            KITSUDECK_GET_MAKRO_IMG, HTTP_POST, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "You've made a POST request\n\n WoW"); },
            NULL, handleGetKitsuDeckMacroImg);
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