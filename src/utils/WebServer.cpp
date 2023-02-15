#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "WebServer.h"
#include "Settings.h"

AsyncWebServer server(80);
void startWebServer(void *parameter)
{
}