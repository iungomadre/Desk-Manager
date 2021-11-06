// components.hpp

#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <Adafruit_NeoPixel.h>

// ESP board
#define LAMP_OUT        D0
#define LAMP_SWITCH     D5

// Pixels
#define LED_PIN         D4
#define NUMPIXELS       15  // ilość LED'ów w pasku

// RGB
#define RED_OUT         D2  // TODO
#define GREEN_OUT       D1  // TODO
#define BLUE_OUT        D3  // TODO

// MONO
#define LED_MONO_OUT    D6  // TODO

// Relay
#define ON              1
#define OFF             0
#define BUTTON_PRESSED  0


void setPixelsColor(short red, short green, short blue, float brightness, Adafruit_NeoPixel &pixels);
// Sets color of pixels

void setRGBcolor(short red, short green, short blue, float brightness);
// Sets color of RGB

void setMONObrightness(float brightness);
// Changes brightness of mono LED. For turning off set 0

class Relay
// Represents physical Relay
{
private:
    bool status;    // turned ON or  OFF
    int pin;        // ESP pin that Relay is connected to

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
// toggles lamp ON or OFF after clicking physical button


#endif // _COMPONENTS_H