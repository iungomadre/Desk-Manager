// components.cpp

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#include "../include/components.hpp"


void setColor(short red, short green, short blue, float brightness, Adafruit_NeoPixel &pixels)
{
    // assert red, green and blue are positive and <256
    // Serial.println(red);
    // Serial.println(green);
    // Serial.println(blue);

    for (unsigned long i = 0; i < NUMPIXELS; i++)
    {
        pixels.setPixelColor(i, red*brightness, green*brightness, blue*brightness);
        delay(5);
        pixels.show();
    }
    
    analogWrite(RED_OUT, static_cast<int>(map(red, 0, 255, 0, 1023) * brightness));
    analogWrite(GREEN_OUT, static_cast<int>(map(green, 0, 255, 0, 1023) * brightness));
    analogWrite(BLUE_OUT, static_cast<int>(map(blue, 0, 255, 0, 1023) * brightness)); 
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

    digitalWrite(pin, status);
};

void setMonoLEDbrightness(float brightness)
{
  analogWrite(LED_MONO_OUT, 1023 * brightness);
}
