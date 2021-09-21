// components.cpp

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#include "../include/components.h"


void setColor(short red, short green, short blue, float brightness, Adafruit_NeoPixel &pixels)
{
    // assert red, green and blue are positive and <256
    Serial.println(red);
    Serial.println(green);
    Serial.println(blue);

    for (unsigned long i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, red*brightness, green*brightness, blue*brightness);
        delay(5);
        pixels.show();
    }
}

void checkButtonPressed(Relay &lamp, unsigned long &time)
{
    bool buttonPressed;
    if(abs(millis() - time > 100))
    {
        time = millis();
        buttonPressed = digitalRead(LAMP_SWITCH);
        if(buttonPressed == BUTTON_PRESSED)
            lamp.toggle();
    }
}

void Relay::toggle()
{
    if(status == ON)
        status = OFF;
    else
        status = ON;
};
