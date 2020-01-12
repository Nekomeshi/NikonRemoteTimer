#ifndef __UTILS_H__
#define __UTILS_H__
#include <Arduino.h>

#define MY_DEBUG
#define ABS(a) ((a) > 0? (a):-(a))//arduinoのabs()はfloat/doubleはintにされてしまう
extern bool readPin(int pin, int highLow, int chatterTimeMS);
#endif
