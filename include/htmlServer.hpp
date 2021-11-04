// htmlServer.hpp
// contains elements needed to run web interface for controlling board

#if !defined(_HEML_SERVER_HPP)
#define _HEML_SERVER_HPP

#include <ESP8266WiFi.h>
#include <./components.hpp>


void printHTML(WiFiClient& client);
// sends HTML code to available client

// decoders:
// decode requested parameters, put results to values passed
void decodeRequestedColors(String& request, int& red, int& green, int& blue);
void decodeRequestedAnimations(String& request, bool* animationsToPlay);
void decodeRequestedBrightness(String& request, float& brightness);
void decodeRequestedLampSwitch(String& request, Relay& lamp);

#endif // _HEML_SERVER_HPP
