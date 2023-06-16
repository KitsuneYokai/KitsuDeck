#ifndef _EVENTS_H
#define _EVENTS_H

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

// --- DEVICE EVENTS (brightness, pin, etc) ---
#define EVENT_CLIENT_AUTH "CLIENT_AUTH"
#define EVENT_SET_BRIGHTNESS "SET_BRIGHTNESS"
#define EVENT_GET_BRIGHTNESS "GET_BRIGHTNESS"

// --- MACRO EVENTS ---
#define EVENT_GET_MACRO_IMAGES "GET_MACRO_IMAGES"
#define EVENT_DELETE_MACRO_IMAGE "DELETE_MACRO_IMAGE"
#define EVENT_CREATE_MACRO "CREATE_MACRO"
#define EVENT_EDIT_MACRO "EDIT_MACRO"
#define EVENT_DELETE_MACRO "DELETE_MACRO"
#define EVENT_GET_MACROS "GET_MACROS"
#define EVENT_GET_MACRO "GET_MACRO"
#define EVENT_UPDATE_MACRO_LAYOUT "UPDATE_MACRO_LAYOUT"

// --- DEVICE EVENTS (brightness, pin, etc) ---
void sendAuthRequest(AsyncWebSocketClient *client);
void handleClientAuthEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleSetBrightnessEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleGetBrightnessEvent(AsyncWebSocketClient *client);

// --- MACRO EVENTS ---
void handleGetMacroImagesEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleDeleteMacroImageEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleCreateMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleEditMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleDeleteMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleGetMacrosEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleGetMacroEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);
void handleUpdateMacroLayoutEvent(AsyncWebSocketClient *client, DynamicJsonDocument &json);

#endif
