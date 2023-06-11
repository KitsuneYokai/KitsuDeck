#include <SD.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

#include "events.h"
#include "../../settings.h"
#include "../../Database/Sqlite.h"
#include "../../Screen.h"
#include "../../../ui/ui.h"

// sends the current auth status to the client (protected or not)
void sendAuthRequest(AsyncWebSocketClient *client)
{
    if (getSettings("auth_pin") != "")
    {
        StaticJsonDocument<200> doc;
        doc["event"] = EVENT_CLIENT_AUTH;
        doc["protected"] = true;
        client->text(doc.as<String>());
    }
    else
    {
        StaticJsonDocument<200> doc;
        doc["event"] = EVENT_CLIENT_AUTH;
        doc["protected"] = false;
        client->text(doc.as<String>());
    }
}

// EVENT_CLIENT_AUTH event function
void handleClientAuthEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    String pin = json["auth_pin"];
    if (getSettings("auth_pin") == pin)
    {
        DynamicJsonDocument response(200);
        response["event"] = EVENT_CLIENT_AUTH "_SUCCESS";
        client->text(response.as<String>());
    }
    else
    {
        DynamicJsonDocument response(200);
        response["event"] = EVENT_CLIENT_AUTH "_FAILED";
        client->text(response.as<String>());
        client->close();
    }
}

// EVENT_SET_BRIGHTNESS event function
void handleSetBrightnessEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json)
{
    if (getSettings("auth_pin") != json["auth_pin"])
    {
        client->close();
    }
    else
    {
        setLCDBrightness(json["value"].as<int>());
        int value = (json["value"].as<int>() * 100) / 255;
        lv_arc_set_value(ui_ScreenBrightnessArk, value);
        setSettings("brightness", String(json["value"].as<int>()));
    }
}

// EVENT_GET_BRIGHTNESS event function
void handleGetBrightnessEvent(AsyncWebSocketClient *client)
{
    DynamicJsonDocument response(200);
    response["event"] = "GET_BRIGHTNESS";
    response["value"] = getSettings("brightness").toInt();
    client->text(response.as<String>());
}