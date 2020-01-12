#ifndef __TIMER_AREA_H__
#define __TIMER_AREA_H__
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
enum{
	TIMER_SET_HOUR = 0,
	TIMER_SET_MINUTE,
	TIMER_SET_SEC,
	TIMER_SET_NONE
};
#define TIMER_SET_NUM TIMER_SET_NONE


class TimerArea{
private:
	int mSec;
	int mMinute;
	int mHour;
	int mSettingHMS;
	int mLeft;
	int mBottom;
	Adafruit_SSD1306 *m_pScreen;

public:
	TimerArea(Adafruit_SSD1306 *scrn, int left, int bottom);
	void setTimeSec(unsigned long sec);
	unsigned long getTimeSec(void);
	void setSettingHMS(int settingHMS);
	void shiftSettingHMSLeft();
	void shiftSettingHMSRight();
	
	bool increment();
	bool decrement();
	
	void show();
};

#endif
