#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "../wifiUtils.h"
#include "../Settings.h"
#include "WebServer.h"
#include "../Screen.h"

#include "../wifiUtils.h"
// define the web server and websocket server objects
AsyncWebServer server(SERVER_PORT);
AsyncWebSocket webSocket(WEBSOCKET_ENDPOINT);

void handleWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    // Handle WebSocket event
    if (type == WS_EVT_CONNECT)
    {
        if (getSettings("auth_pin") != "")
        {
            StaticJsonDocument<200> doc;
            doc["event"] = "CLIENT_AUTH";
            doc["protected"] = true;
            client->text(doc.as<String>());
        }
        else
        {
            StaticJsonDocument<200> doc;
            doc["event"] = "CLIENT_AUTH";
            doc["protected"] = false;
            client->text(doc.as<String>());
        }
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        return;
    }
    else if (type == WS_EVT_ERROR)
    {
        Serial.printf("WebSocket client #%u error(%u): %s\n", client->id(), *((uint16_t *)arg), (char *)data);
    }
    else if (type == WS_EVT_DATA)
    {
        DynamicJsonDocument doc(4096);
        DeserializationError error = deserializeJson(doc, data);
        if (doc["event"] == "CLIENT_AUTH")
        {
            String pin = doc["auth_pin"];
            if (getSettings("auth_pin") == pin)
            {
                DynamicJsonDocument response(200);
                response["event"] = "CLIENT_AUTH_SUCCESS";
                client->text(response.as<String>());
            }
            else
            {
                DynamicJsonDocument response(200);
                response["event"] = "CLIENT_AUTH_FAILED";
                client->text(response.as<String>());
                client->close();
            }
        }

        if (doc["event"] == "SET_BRIGHTNESS")
        {
            if (getSettings("auth_pin") != doc["auth_pin"])
            {
                client->close();
            }
            else
            {
                setLCDBrightness(doc["value"].as<int>());
                setSettings("brightness", String(doc["value"].as<int>()));
            }
        }
        if (doc["event"] == "GET_BRIGHTNESS")
        {
            DynamicJsonDocument response(200);
            response["event"] = "GET_BRIGHTNESS";
            response["value"] = getSettings("brightness").toInt();
            client->text(response.as<String>());
        }
    }
}
// Handle HTTP GET request for /
void handleRootRequest(AsyncWebServerRequest *request)
{
    // make a json
    String ip = WiFi.localIP().toString();
    String hostname = getKitsuDeckHostname();
    DynamicJsonDocument doc(200);
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
        DynamicJsonDocument doc(200);
        DynamicJsonDocument response(200);
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
            vTaskDelay(5000 / portTICK_PERIOD_MS); // Wait for 5 seconds
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