#ifndef _KITSUDECK_H_
#define _KITSUDECK_H_
#include <ESPAsyncWebServer.h>

// Auth.cpp
void handleKitsuDeckAuthRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

// addMakro.cpp
void handleKitsuDeckAddMakroRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

// getMakros.cpp
void handleKitsuDeckGetMakrosRequest(AsyncWebServerRequest *request);

// getMakroImg.cpp
void handleGetKitsuDeckMacroImg(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

// getSystemInfo.cpp
void handleGetKitsuDeckSystemInfo(AsyncWebServerRequest *request);

#endif