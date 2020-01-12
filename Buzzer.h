#ifndef __BUZZER_H__
#define __BUZZER_H__
#include <Arduino.h>
class Buzzer
{
private:
	int mPin;
	unsigned long mSoundEndTime;
	
	void noTone();
	void tone(int freq);

public:
	Buzzer(int pin);
	void startBuzz(int hz, unsigned long duration);
	void updateBuzz();
	void stopBuzz();
};

#endif
