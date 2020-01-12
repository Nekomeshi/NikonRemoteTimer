#include "Utils.h"

bool readPin(int pin, int highLow, int chatterTimeMS){
	int a = digitalRead(pin);
	delay(chatterTimeMS);
	int b = digitalRead(pin);
	return a == highLow && b == highLow;
}
