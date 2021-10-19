// htmlServer.cpp

#include <ESP8266WiFi.h>
#include "../include/htmlServer.hpp"

int getAvailableClient(WiFiServer& from, WiFiClient& to)
{
    to = from.available();
    if (!to) {
        return CLIENT_NOT_AVAILABLE_ERROR;
    }
    unsigned int timewate = 0;
    while (!to.available()) {
        delay(1);
        if (++timewate > 1800)
        {
        //timeout
        to.stop();
        return CLIENT_UNREACHABLE_ERROR;
        }
    }
    return 0;
}

void decodeRequestedColors(String request, int& red, int& green, int& blue)
{
    String colorHex = "";
    int i = 0;
    
    if (request.charAt(5) != '%');
    else
    {
        while (i < request.length())
        {
        if (request.charAt(i) == '%' && request.charAt(i + 1) == '2' && request.charAt(i + 2) == '3')
        {
            for (int m = i + 3; m < i + 9; m++) colorHex += request.charAt(m);
            break;
        }
        i++;
        }

        int number;
        number = (int) strtoll(&colorHex[0], NULL, 16);

        red = number >> 16;
        green = number >> 8 & 0xFF;
        blue = number & 0xFF;
    }
}

void decodeRequestedAnimations(String request, bool* animationsToPlay)
{
    if (request.indexOf("/LEDOFF") != -1)
    {
        animationsToPlay[0] = false;
        animationsToPlay[1] = false;
    }
    else if (request.indexOf("/ANIM1") != -1)
    {
        animationsToPlay[0] = true;
        animationsToPlay[1] = false;
    }
    else if (request.indexOf("/ANIM2") != -1)
    {
        animationsToPlay[0] = false;
        animationsToPlay[1] = true;
    }
}

void decodeRequestedBrightness(String request, float& brightness)
{
    if (request.indexOf("/LED50") != -1)
    {
        brightness=0.5;
    }
    else if (request.indexOf("/LED100") != -1)
    {
        brightness=1;
    }
}


