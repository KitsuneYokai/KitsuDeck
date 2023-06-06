#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

// define the server port / websocket endpoint
#define SERVER_PORT 80
#define WEBSOCKET_ENDPOINT "/ws"
// define the api endpoints
#define ROOT_ENDPOINT "/"
#define AUTH_ENDPOINT "/auth"
#define GET_MACRO_IMAGE "/getMacroImage"
#define POST_MACRO_IMAGE "/postMacroImage"

void startWebServer(void *parameter);

#endif
