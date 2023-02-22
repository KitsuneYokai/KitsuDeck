#ifndef _KITSUDECK_AUTH_H_
#define _KITSUDECK_AUTH_H_
#include <ESPAsyncWebServer.h>

void handleKitsuDeckAuthRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);

#endif