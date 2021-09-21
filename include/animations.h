// animations.h

#if !defined(_ANIMATIONS_H)
#define _ANIMATIONS_H

#define ENTRY_ANIMATION     0
#define ANIMATION_1         1
#define ANIMATION_2         2

void Animate(unsigned int animationID, float brightness, Adafruit_NeoPixel &pixels);
/*
Performs animation based on their ID

Params:
-------
animationID: unsigned int
    ID of animation to perform

brightness: float
    brightness of animation

pixels: Adafruit_Neopixel&
    reference to Adafruit_Neopixel object controlling LED's
*/

#endif // _ANIMATIONS_H
