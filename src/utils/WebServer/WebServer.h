#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

// define the server port / websocket endpoint
#define SERVER_PORT 80
#define WEBSOCKET_ENDPOINT "/ws"
// define the api endpoints
#define ROOT_ENDPOINT "/"
#define KITSUDECK_AUTH "/kitsuDeck/auth"

void startWebServer(void *parameter);

#endif
