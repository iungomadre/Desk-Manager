// components.cpp

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../include/components.hpp"


void setPixelsColor(short red, short green, short blue, float brightness, Adafruit_NeoPixel &pixels)
{
    for (unsigned long i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, red*brightness, green*brightness, blue*brightness);
        delay(5);
        pixels.show();
    }
}

void setRGBcolor(short red, short green, short blue, float brightness)
{
    analogWrite(RED_OUT, static_cast<int>(map(red, 0, 255, 0, 1023) * brightness));
    analogWrite(GREEN_OUT, static_cast<int>(map(green, 0, 255, 0, 1023) * brightness));
    analogWrite(BLUE_OUT, static_cast<int>(map(blue, 0, 255, 0, 1023) * brightness)); 
}

void setMONObrightness(float brightness)
{
  analogWrite(LED_MONO_OUT, 1023 * brightness);
}

void Relay::toggle()
{
    if(status == ON)
        status = OFF;
    else
        status = ON;

    digitalWrite(pin, status);
};

void checkButtonPressed(Relay &lamp, unsigned long &time)
{
    bool buttonPressed;
    if(millis() - time > 250)
    {
        time = millis();
        buttonPressed = digitalRead(LAMP_SWITCH);
        if(buttonPressed == BUTTON_PRESSED)
            lamp.toggle();
    }
}
