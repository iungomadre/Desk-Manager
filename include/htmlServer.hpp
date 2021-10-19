// htmlServer.hpp
// contains all elements needed to run web interface for controlling board

#if !defined(_HEML_SERVER_HPP)
#define _HEML_SERVER_HPP

#include <ESP8266WiFi.h>

#define CLIENT_NOT_AVAILABLE_ERROR -1
#define CLIENT_UNREACHABLE_ERROR -2

void hostHTML();
// sends html code and reads reply from available client

int getAvailableClient(WiFiServer& from, WiFiClient& to);
// finds available client connected to server

void executeGetRequest();
// modifies board variables to match client request

void printHTML();
// prints HTML to available client

// decoders:
void decodeRequestedBrightness(String request, float& brightness);
void decodeRequestedAnimations(String request, bool* animationsToPlay);
void decodeRequestedColors(String request, int& red, int& green, int& blue);



#endif // _HEML_SERVER_HPP
