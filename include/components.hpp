// components.hpp

#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <Adafruit_NeoPixel.h>

#define CONNECTION_OK   0
#define NUMPIXELS       15

// programmable
#define LED_PIN         D4
#define LAMP_OUT        D0
#define LAMP_SWITCH     D5

// RGB
#define RED_OUT         D2  // TODO
#define GREEN_OUT       D1  // TODO
#define BLUE_OUT        D3  // TODO

// mono
#define LED_MONO_OUT    D6  // TODO

#define ON              1
#define OFF             0
#define BUTTON_PRESSED  0

void setColor(short red, short green, short blue, float brightness, Adafruit_NeoPixel &pixels);
/*
Sets color of LEDs

Params:
-------
red: short
    8-bit value of red factor (value must be between 0 and 256)

green: short
    8-bit value of green factor (value must be between 0 and 256) <---------- czy na pewno???

blue: short
    8-bit value of blue factor

brightness: float
    brightness of LED to be set (value must be between 0 and 256)

pixels: Adafruit_Neopixel&
    reference to Adafruit_Neopixel object controlling LED's
*/

class Relay
{
private:
    bool status;    // is turned ON or  OFF
    int pin;        // chyba niepotrzebne, więc może klasa też niepotrzebna

public:
    // Default constructor disabled

    Relay(int outputPin) : status(OFF), pin(outputPin) {};
    // Parametrized constructor

    Relay(int outputPin, bool status) : status(status), pin(outputPin) {};
    // Parametrized constructor

    void toggle();
    // Switches Relay toggle on and off

    bool getStatus() { return status; };
};

void checkButtonPressed(Relay &lamp, unsigned long &time);
// toggles lamp on and off after clicking physical button

void setMonoLEDbrightness(float brightness);
// changes brightness of mono LED. For turning off set 0

#endif // _COMPONENTS_H