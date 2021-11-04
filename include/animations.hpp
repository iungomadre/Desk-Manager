// animations.hpp

#if !defined(_ANIMATIONS_H)
#define _ANIMATIONS_H

#define NUM_ANIMATIONS          5   // ilość wszystkich animacji

#define MONO_ANIMATION_1        0
#define PIXELS_ENTRY_ANIMATION  1
#define PIXELS_ANIMATION_1      2
#define PIXELS_ANIMATION_2      3
#define RGB_ANIMATION_1         4

void animatePixels(unsigned int animationID, float brightness, Adafruit_NeoPixel &pixels);

void animateRGB(unsigned int animationID);

void animateMONO(unsigned int animationID);


#endif // _ANIMATIONS_H
