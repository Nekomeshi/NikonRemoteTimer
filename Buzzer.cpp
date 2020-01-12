#include "Buzzer.h"

#define LEDC_CHANNEL_2     2
#define LEDC_TIMER_13_BIT  13
#define LEDC_BASE_FREQ     5000

Buzzer::Buzzer(int pin){
	mPin = pin;
	mSoundEndTime = 0;
	ledcSetup(LEDC_CHANNEL_2, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT) ;
	ledcAttachPin(mPin, LEDC_CHANNEL_2) ; // CH2をSOUNDERに
}

void Buzzer::noTone()
{
  	ledcWriteTone(LEDC_CHANNEL_2, 0) ;
}

void Buzzer::tone(int freq)
{
  	ledcWriteTone(LEDC_CHANNEL_2, freq) ;
}
void Buzzer::startBuzz(int hz, unsigned long duration){	
	mSoundEndTime = millis() + duration;
  	tone(hz);
	//http://www.microfan.jp/esp32/workshop/tone
}
void Buzzer::updateBuzz(){
	if(mSoundEndTime == 0) return;
	if(millis() > mSoundEndTime){
		stopBuzz();
	}
}
void Buzzer::stopBuzz(){
	if(mSoundEndTime == 0) return;
	noTone();
	mSoundEndTime = 0;
}
