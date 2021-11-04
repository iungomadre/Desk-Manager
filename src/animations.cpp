// animations.cpp

#include <Adafruit_NeoPixel.h>
#include "../include/animations.hpp"
#include "../include/components.hpp"


void animatePixels(unsigned int animationID, float brightness, Adafruit_NeoPixel &pixels)
{
    switch(animationID)
    {
    case PIXELS_ENTRY_ANIMATION:
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i,0,200,0);
            pixels.show();
            delay(100);
        }
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i,0,0,0);
            pixels.show();
            delay(50);
        }
        break;

    case PIXELS_ANIMATION_1:
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i,
                                 (sin((float)millis()/1000 + (float)i/10)+1)*127*brightness,
                                 (sin(((float)millis())/1000 + 2.4 + (float)i/10) +1)*127*brightness,
                                 (sin(((float)millis())/1000 + 4.8 + (float)i/10) +1)*127*brightness);
            delay(1);
        }
        pixels.show();
        break;

    case PIXELS_ANIMATION_2:
        for(int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i, 
                                 (float)random(0,255)*brightness, 
                                 (float)random(0,255)*brightness, 
                                 (float)random(0,255)*brightness);
            pixels.show();
            delay(50);
        }
        for(int i = NUMPIXELS - 1; i > -1; i--)
        {
            pixels.setPixelColor(i, 
                                 (float)random(0,255)*brightness, 
                                 (float)random(0,255)*brightness, 
                                 (float)random(0,255)*brightness);
            pixels.show();
            delay(50);
        }
        break;

    default:
        Serial.println("Cannot perform animation of ID given");
        return;
    }

}

void animateRGB(unsigned int animationID)
{
    switch(animationID)
    {
    case RGB_ANIMATION_1:
        setRGBcolor(255, 0, 0, 1);
        delay(500);
        
        setRGBcolor(0, 255, 0, 1);
        delay(500);
        
        setRGBcolor(0, 0, 255, 1);
        delay(500);
        
        setRGBcolor(255, 255, 255, 1);
        break;

    default:
        Serial.println("Cannot perform animation of ID given");
        return;
    }

}

void animateMONO(unsigned int animationID)
{
    switch(animationID)
    {
    case MONO_ANIMATION_1:
        setMONObrightness(1);
        delay(100);

        setMONObrightness(0);
        delay(100);

        setMONObrightness(1);
        delay(100);

        setMONObrightness(0);
        delay(100);

        setMONObrightness(1);
        break;

    default:
        Serial.println("Cannot perform animation of ID given");
        return;
    }

}