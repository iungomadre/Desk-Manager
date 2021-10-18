// setBuiltInDiode.hpp
// mock file created to test unit testing

#if !defined(_SET_BUILT_IN_DIODE_H)
#define _SET_BUILT_IN_DIODE_H

#include <Arduino.h>

void setBuiltinDiode(int state)
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, state);
}


#endif // _SET_BUILT_IN_DIODE_H



