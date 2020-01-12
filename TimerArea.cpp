#include "TimerArea.h"
#include <Fonts/FreeSans9pt7b.h>
#include "ScreenInfo.h"

TimerArea::TimerArea(Adafruit_SSD1306 *scrn, int left, int bottom)
{
	mSec = mMinute = mHour = 0;
	mSettingHMS = TIMER_SET_NONE;
	mLeft = left;
	mBottom = bottom;
	m_pScreen = scrn;

}


void TimerArea::setTimeSec(unsigned long sec)
{
	mHour = sec/3600;
	mMinute = (sec - mHour*3600)/60;
	mSec = sec - mHour*3600 - mMinute*60;
}
unsigned long TimerArea::getTimeSec(void)
{
	return mHour*3600 + mMinute*60 + mSec;
}

void TimerArea::setSettingHMS(int settingHMS)
{
	mSettingHMS = settingHMS;
}

void TimerArea::shiftSettingHMSLeft()
{
	mSettingHMS = (mSettingHMS + TIMER_SET_NUM - 1) % TIMER_SET_NUM;
	Serial.println(mSettingHMS);
}
void TimerArea::shiftSettingHMSRight()
{
	mSettingHMS = (mSettingHMS + 1) % TIMER_SET_NUM;
}

bool TimerArea::increment()
{
	switch(mSettingHMS){
		case TIMER_SET_HOUR:
			mHour = (mHour+1)%24;
			break;
		case TIMER_SET_MINUTE:
			mMinute = (mMinute+1)%60;
			break;
		case TIMER_SET_SEC:
			mSec = (mSec+1)%60;
			break;
		default:
			return false;
	}
	return true;
}
bool TimerArea::decrement()
{
	switch(mSettingHMS){
		case TIMER_SET_HOUR:
			mHour = (mHour+23)%24;
			break;
		case TIMER_SET_MINUTE:
			mMinute = (mMinute+59)%60;
			break;
		case TIMER_SET_SEC:
			mSec = (mSec+59)%60;
			break;
		default:
			return false;		
	}
	return true;
}

void TimerArea::show()
{
  	m_pScreen->setTextWrap(false);
  	m_pScreen->setFont(&FreeSans9pt7b);
  	m_pScreen->setTextSize(1);  	
  	m_pScreen->setTextColor(WHITE);

  	char tmp[3];
  	int l = mLeft;
  	m_pScreen->setCursor(mLeft,mBottom);
  	sprintf(tmp, "%02d", mHour);
  	m_pScreen->print(tmp);
	if(mSettingHMS == TIMER_SET_HOUR) drawFrame(m_pScreen, l-4, mBottom - 16, 27, 20);
  	l += 28;
  	
  	m_pScreen->setCursor(l,mBottom);
  	m_pScreen->print(":");
  	l+=14;
  	
  	m_pScreen->setCursor(l,mBottom);
  	sprintf(tmp, "%02d", mMinute);
  	m_pScreen->print(tmp);
	if(mSettingHMS == TIMER_SET_MINUTE) drawFrame(m_pScreen, l-4, mBottom- 16, 27, 20);
	l += 28;

  	m_pScreen->setCursor(l,mBottom);
  	m_pScreen->print(":");
  	l+=14;

  	m_pScreen->setCursor(l,mBottom);
  	sprintf(tmp, "%02d", mSec);
  	m_pScreen->print(tmp);	
	if(mSettingHMS == TIMER_SET_SEC) drawFrame(m_pScreen, l-4, mBottom- 16, 27, 20);
}
