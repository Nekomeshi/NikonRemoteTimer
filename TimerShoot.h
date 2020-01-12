#ifndef __TIMER_SHOOT_H__
#define __TIMER_SHOOT_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TimerArea.h"
#include "SettingItem.h"
#include "CaptureCtrl.h"
#include "TimerSetting.h"

class TimerRepeatArea{
private:
	Adafruit_SSD1306 *m_pScreen;
	int mLeft;
	int mBottom;
	int mTotalCount;
	int mRepeatCount;
	
public:
	TimerRepeatArea(Adafruit_SSD1306 *scrn, int left, int bottom);
	void setRepeatCount(int repCount);
	int getRepeatCount(void);
	void setTotalCount(int totalCount);
	
	void show();
};


class TimerShoot{
private:
	Adafruit_SSD1306 *m_pScreen;
	CaptureCtrl		*m_pCaptureCtrl;
	TimerArea 		*m_pTimerArea;
	SettingItem 	**m_pSettingItems;
	TimerRepeatArea *m_pTimerRepeatArea;
	TimerSettingData mTimerData;

	int mRepeatCount;
	int mCurrentItem;
	bool mUseAF;
	unsigned long mStartTimeMS;
	int mRemainingTime;
	void show();
	void (*onTimerEndCB)(bool isCompleted);
	void stopTimer(bool isCompleted);
	
public:
	TimerShoot(Adafruit_SSD1306 *scrn, CaptureCtrl *cap);
	virtual ~TimerShoot();
	void setTimerData(TimerSettingData timerData);
	void startTimer(bool useAF);
	void stopTimer();
	void updateTimer();

	void setOnTimerEnd(void (*cb)(bool));

	
};

#endif
