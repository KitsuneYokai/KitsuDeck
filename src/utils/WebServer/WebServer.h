#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

// define the server port / websocket endpoint
#define SERVER_PORT 80
#define WEBSOCKET_ENDPOINT "/ws"
// define the api endpoints
#define ROOT_ENDPOINT "/"
#define KITSUDECK_AUTH "/kitsuDeck/auth"
#define KITSUDECK_ADD_MAKRO "/kitsuDeck/addMakro"
#define KITSUDECK_GET_MAKROS "/kitsuDeck/getMakros"
#define KITSUDECK_GET_MAKRO_IMG "/kitsuDeck/getMacroImg" // TODO: rename Makro to Macro in all files (oops :D)

void startWebServer(void *parameter);

#endif
