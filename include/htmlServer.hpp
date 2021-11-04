// htmlServer.hpp
// contains all elements needed to run web interface for controlling board

#if !defined(_HEML_SERVER_HPP)
#define _HEML_SERVER_HPP

#include <ESP8266WiFi.h>
#include <./components.hpp>

#define CLIENT_NOT_AVAILABLE_ERROR -1
#define CLIENT_UNREACHABLE_ERROR -2
#define CLIENT_OK 1


int getAvailableClient(WiFiServer& from, WiFiClient& to);
// finds available client connected to server

void printHTML(WiFiClient& client);
// sends HTML code to available client

// decoders:
void decodeRequestedColors(String request, int& red, int& green, int& blue);
void decodeRequestedAnimations(String request, bool* animationsToPlay);
void decodeRequestedBrightness(String request, float& brightness);
void decodeRequestedLampSwitch(String request, Relay& lamp);

#endif // _HEML_SERVER_HPP
