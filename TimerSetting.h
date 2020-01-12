#ifndef __TIMER_SETTING_H__
#define __TIMER_SETTING_H__
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "TimerArea.h"
#include "SettingItem.h"

struct TimerSettingData{
	unsigned int delaySec;
	unsigned int durationSec;
	unsigned int intervalSec;
	unsigned int repeat;
	bool sound;
};
enum {
	UP_KEY = 0,
	DOWN_KEY,
	LEFT_KEY,
	RIGHT_KEY,
	OK_KEY,
	MENU_KEY,
	KEY_NUM
};

#define NO_KEY KEY_NUM



class RepeatArea{
private:
	int mRepeatCount;
	Adafruit_SSD1306 *m_pScreen;
	bool mIsOn;
	int mLeft;
	int mBottom;

public:
	RepeatArea(Adafruit_SSD1306 *scrn, int left, int bottom);
	void setRepeatCount(int repCount);
	int getRepeatCount(void);
	void setOn(bool isOn);
	bool increment();
	bool decrement();
	
	void show();
};

class SoundArea{
private:
	bool mSoundOn;
	Adafruit_SSD1306 *m_pScreen;
	bool mIsOn;
	int mLeft;
	int mBottom;

public:
	SoundArea(Adafruit_SSD1306 *scrn, int left, int bottom);
	void setSoundOn(bool isOn);
	bool isSoundOn(void);
	void setOn(bool isOn);
	bool invertOn();
	
	void show();
};

class CameraArea{
private:
	bool mIsCameraAvailable;
	Adafruit_SSD1306 *m_pScreen;
	int mLeft;
	int mBottom;

public:
	CameraArea(Adafruit_SSD1306 *scrn, int left, int bottom);
	void setCameraAvailable(bool camAvailable);
	bool isCameraAvailable();
	void show();	
};

class TimerSetting
{
private:
	int mPins[KEY_NUM];
	bool isKey(int pin, int key){return mPins[key] == pin;};
	SettingItem **mSettingItems;
	TimerArea *mTimerArea;
	RepeatArea *mRepeatArea;
	SoundArea *mSoundArea;
	CameraArea *mCameraArea;
	int mSettingItem;
	bool mIsEditting;
	
	TimerSettingData mTimerSettingData;
	Adafruit_SSD1306 *m_pScreen;

	int mLongPressKey;
	unsigned long mLongPressedTime;

	void endEditting();
public:
	TimerSetting(Adafruit_SSD1306 *scrn, int pins[]);
	~TimerSetting();

	void setTimerData(TimerSettingData timerData);
	TimerSettingData getTimerData(void);

	void setCameraAvailable(bool cameraAvailable);

	void showTimerSetting(bool isInit);
	void updateTimerSetting();
	void dismissTimerSetting();
	
	void onKeyPressed(int pin);
	void onKeyLongPressed(int pin);
	void onKeyReleased(int pin);


};


#endif
