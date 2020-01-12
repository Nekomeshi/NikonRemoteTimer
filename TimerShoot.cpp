#include "TimerShoot.h"
#include <string.h>
#include <Fonts/TomThumb.h>
#include <Fonts/FreeSans9pt7b.h>

enum{
	TIMER_DELAY = 0,
	TIMER_SHOOT,
	TIMER_INTERVAL,
	TIMER_ITEM_NUM
};

static const String TIMER_NAMES[TIMER_ITEM_NUM] ={
	"DELAY",
	"SHOOT",
	"INTVL",
};

TimerRepeatArea::TimerRepeatArea(Adafruit_SSD1306 *scrn, int left, int bottom)
{
	m_pScreen = scrn;
	mLeft = left;
	mBottom = bottom;
	mRepeatCount = 0;
	mTotalCount = 0;

}
void TimerRepeatArea::setRepeatCount(int repCount)
{
	mRepeatCount = repCount;
}
int TimerRepeatArea::getRepeatCount(void)
{
	return mRepeatCount;
}
void TimerRepeatArea::setTotalCount(int totalCount)
{
	mTotalCount = totalCount;
}
	
void TimerRepeatArea::show()
{
  	m_pScreen->setTextWrap(false);
  	m_pScreen->setFont(&FreeSans9pt7b);
  	m_pScreen->setTextSize(1);  	
  	m_pScreen->setTextColor(WHITE);

  	char tmp[20];
  	m_pScreen->setCursor(mLeft,mBottom);
  	if(mTotalCount > 0){
	  	sprintf(tmp, "Rep: %03d / %03d", mRepeatCount, mTotalCount);  		
  	}
  	else{
	  	sprintf(tmp, "Rep: %03d / Inf", mRepeatCount);  		
  	}
  	m_pScreen->print(tmp);	
}


TimerShoot::TimerShoot(Adafruit_SSD1306 *scrn, CaptureCtrl *cap)
{
	m_pScreen = scrn;
	m_pCaptureCtrl = cap;
	m_pTimerArea = new TimerArea(scrn, 10, 32);
	m_pTimerRepeatArea = new TimerRepeatArea(scrn, 8, 56);

	m_pSettingItems = new SettingItem*[TIMER_ITEM_NUM];
	for(int i = 0;i < TIMER_ITEM_NUM;i++){
		m_pSettingItems[i] = new SettingItem(scrn, TIMER_NAMES[i], i*25 + 4, 8, 25, 6);	
	}
}

TimerShoot::~TimerShoot()
{
	for(int i = 0;i < TIMER_ITEM_NUM;i++){
		delete m_pSettingItems[i];		
	}
	delete [] m_pSettingItems;
	delete m_pTimerArea;
	delete m_pTimerRepeatArea;
}


void TimerShoot::show()
{
	m_pScreen->clearDisplay();
	for(int i = 0;i < TIMER_ITEM_NUM;i++){
		m_pSettingItems[i]->setOn(i == mCurrentItem);
		m_pSettingItems[i]->show();	
	}
	m_pTimerArea->show();
	m_pTimerRepeatArea->show();
	m_pScreen->display();
}

void TimerShoot::setTimerData(TimerSettingData timerData)
{
	mTimerData = timerData;	
}

void TimerShoot::setOnTimerEnd(void (*cb)(bool))
{
	onTimerEndCB = cb;
}

//struct TimerSettingData{
//	unsigned int delaySec;
//	unsigned int durationSec;
//	unsigned int intervalSec;
//	unsigned int repeat;
//	bool sound;
//};


void TimerShoot::startTimer(bool useAF)
{
	mCurrentItem = TIMER_DELAY;
	mUseAF = useAF;
	mStartTimeMS = millis();
	mRemainingTime = mTimerData.delaySec;
	m_pTimerArea->setTimeSec(mRemainingTime);
	mRepeatCount = 1;
	m_pTimerRepeatArea->setRepeatCount(mRepeatCount);
	m_pTimerRepeatArea->setTotalCount(mTimerData.repeat);
	show();
}
void TimerShoot::stopTimer(bool isCompleted)
{
	if(mCurrentItem == TIMER_SHOOT) m_pCaptureCtrl->stopCapture();
	if(onTimerEndCB != NULL) (*onTimerEndCB)(isCompleted);
}

void TimerShoot::stopTimer()
{
	stopTimer(false);
}

void TimerShoot::updateTimer()
{
	switch(mCurrentItem){
		case TIMER_DELAY:
		{
			int remTime = mTimerData.delaySec - (millis() - mStartTimeMS)/1000;
			if(remTime <= 0){//Delay 終了
				m_pCaptureCtrl->useBuzzer(mTimerData.sound);
				m_pCaptureCtrl->startCapture(mUseAF);
				mCurrentItem = TIMER_SHOOT;
				mStartTimeMS = millis();
				mRemainingTime = mTimerData.durationSec;
				m_pTimerArea->setTimeSec(mRemainingTime);
				show();			
			}
			else if(remTime < mRemainingTime){
				mRemainingTime = remTime;
				m_pTimerArea->setTimeSec(mRemainingTime);
				show();			
			}
		}
		break;
		case TIMER_SHOOT:
		{
			int remTime = mTimerData.durationSec - (millis() - mStartTimeMS)/1000;
			if(remTime <= 0){//キャプチャ時間終了
				if(mTimerData.repeat > 0 && //撮影回数がinfではない
					mRepeatCount >= mTimerData.repeat){//撮影回数こなした
					stopTimer(true);
				}
				else{
					m_pCaptureCtrl->stopCapture();
					mCurrentItem = TIMER_INTERVAL;
					mStartTimeMS = millis();
					mRemainingTime = mTimerData.intervalSec;
					m_pTimerArea->setTimeSec(mRemainingTime);
					show();	
				}
			}
			else if(remTime < mRemainingTime){
				mRemainingTime = remTime;
				m_pTimerArea->setTimeSec(mRemainingTime);
				m_pCaptureCtrl->updateCapture();
				show();			
			}
			else{
				m_pCaptureCtrl->updateCapture();
			}
		}
		break;
		case TIMER_INTERVAL:
		{
			int remTime = mTimerData.intervalSec - (millis() - mStartTimeMS)/1000;
			if(remTime <= 0){//interval終了
				m_pCaptureCtrl->startCapture(mUseAF);//次の撮影開始
				mRepeatCount++;
				m_pTimerRepeatArea->setRepeatCount(mRepeatCount);
				mCurrentItem = TIMER_SHOOT;
				mStartTimeMS = millis();
				mRemainingTime = mTimerData.durationSec;
				m_pTimerArea->setTimeSec(mRemainingTime);
				show();			
			}
			else if(remTime <mRemainingTime){
				mRemainingTime = remTime;
				m_pTimerArea->setTimeSec(mRemainingTime);
				show();			
			}
		}
		break;
	}
}
