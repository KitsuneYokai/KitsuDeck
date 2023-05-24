#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

// define the server port / websocket endpoint
#define SERVER_PORT 80
#define WEBSOCKET_ENDPOINT "/ws"
// define the api endpoints
#define ROOT_ENDPOINT "/"
#define Auth_ENDPOINT "/auth"
#define KITSU_DECK_GET_SYSTEM_INFO "/sysinfo"
void startWebServer(void *parameter);

#endif
