#ifndef __SINGLE_SHOOT_H__
#define __SINGLE_SHOOT_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TimerArea.h"

#include "CaptureCtrl.h"


class SingleShoot{
private:
	Adafruit_SSD1306 *m_pScreen;
	CaptureCtrl		*m_pCaptureCtrl;
	TimerArea *m_pTimerArea;
	bool mMakeSound;
	unsigned long mStartTimeMS;
	unsigned long mLastTickTime;

	void show();

public:
	SingleShoot(Adafruit_SSD1306 *scrn, CaptureCtrl *cap);
	virtual ~SingleShoot();

	void makeSound(bool makeSound);
	void startCapture(bool useAF);
	void stopCapture();
	void updateCapture();
};

#endif
