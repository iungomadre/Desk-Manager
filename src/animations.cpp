// animations.cpp

#include <Adafruit_NeoPixel.h>
#include "../include/animations.hpp"
#include "../include/components.hpp"


void animate(unsigned int animationID, float brightness, Adafruit_NeoPixel &pixels)
{
    switch(animationID)
    {
    case ENTRY_ANIMATION:
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

    case ANIMATION_1:
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

    case ANIMATION_2:
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
    
    case ENTRY_ANIMATION_RGB:
        setColor(255, 0, 0, 1, pixels);
        delay(500);
        
        setColor(0, 255, 0, 1, pixels);
        delay(500);
        
        setColor(0, 0, 255, 1, pixels);
        delay(500);
        
        setColor(255, 255, 255, 1, pixels);
        break;

    default:
        Serial.println("Cannot perform animation of ID given");
        return;
    }

}