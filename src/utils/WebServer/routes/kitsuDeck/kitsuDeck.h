#ifndef _KITSUDECK_H_
#define _KITSUDECK_H_
#include <ESPAsyncWebServer.h>

// Auth.cpp
void handleKitsuDeckAuthRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

// AddMakro.cpp
void handleKitsuDeckAddMakroRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
#endif