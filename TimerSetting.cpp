#include "TimerSetting.h"
#include <string.h>
#include <Fonts/TomThumb.h>
#include <Fonts/FreeSans9pt7b.h>
#include "ScreenInfo.h"
enum{
	SET_DELAY = 0,
	SET_DURATION,
	SET_INTERVAL,
	SET_REPEAT,
	SET_SOUND,
	SET_ITEM_NUM
};

static const String ITEM_NAMES[SET_ITEM_NUM] ={
	"DELAY",
	"DURAT",
	"INTVL",
	"REPET",
	"SOUND"
};


RepeatArea::RepeatArea(Adafruit_SSD1306 *scrn, int left, int bottom)
{
	m_pScreen = scrn;
	mLeft = left;
	mBottom = bottom;
	mRepeatCount = 1;
	mIsOn = false;
}
void RepeatArea::setRepeatCount(int repCount)
{
	mRepeatCount = repCount;
}
int RepeatArea::getRepeatCount(void)
{
	return mRepeatCount;
}
void RepeatArea::setOn(bool isOn)
{
	mIsOn = isOn;
}
bool RepeatArea::increment()
{
	if(!mIsOn) return false;
	mRepeatCount = (mRepeatCount + 1) % 1000;
	Serial.println("increment");
	return true;
}
bool RepeatArea::decrement()
{
	if(!mIsOn) return false;
	mRepeatCount = (mRepeatCount + 999) % 1000;
	return true;
}
void RepeatArea::show()
{
  	m_pScreen->setTextWrap(false);
  	m_pScreen->setFont(&FreeSans9pt7b);
  	m_pScreen->setTextSize(1);  	
  	m_pScreen->setTextColor(WHITE);

  	char tmp[8];
  	m_pScreen->setCursor(mLeft,mBottom);
  	if(mRepeatCount > 0){
	  	sprintf(tmp, "Rep:%03d", mRepeatCount);  		
  	}
  	else{
	  	sprintf(tmp, "Rep:Inf");  		
  	}
  	m_pScreen->print(tmp);	

	if(mIsOn)drawFrame(m_pScreen, mLeft-4, mBottom - 16, 75, 21);
}


SoundArea::SoundArea(Adafruit_SSD1306 *scrn, int left, int bottom)
{
	m_pScreen = scrn;
	mLeft = left;
	mBottom = bottom;
	mSoundOn = false;
	mIsOn = false;
}
void SoundArea::setSoundOn(bool isOn)
{
	mSoundOn = isOn;
}
bool SoundArea::isSoundOn(void)
{
	return mSoundOn;
}
void SoundArea::setOn(bool isOn)
{
	mIsOn = isOn;
}
bool SoundArea::invertOn()
{
	if(!mIsOn) return false;
	mSoundOn = !mSoundOn;
	return true;
}
	
void SoundArea::show()
{
   	if(mSoundOn){
		m_pScreen->drawBitmap(mLeft, mBottom -12,  Resources::note_bmp, 16, 16, WHITE);
  	}
  	else{
		m_pScreen->drawBitmap(mLeft, mBottom -12,  Resources::no_note_bmp, 16, 16, WHITE);
  	}
	if(mIsOn)drawFrame(m_pScreen, mLeft-3, mBottom - 16, 20, 21);	
}

CameraArea::CameraArea(Adafruit_SSD1306 *scrn, int left, int bottom)
{
	m_pScreen = scrn;
	mLeft = left;
	mBottom = bottom;
	mIsCameraAvailable = false;
}
void CameraArea::setCameraAvailable(bool camAvailable)
{
	mIsCameraAvailable = camAvailable;
}
bool CameraArea::isCameraAvailable()
{
	return mIsCameraAvailable;
}
void CameraArea::show()
{
  	if(mIsCameraAvailable){
		m_pScreen->drawBitmap(mLeft, mBottom -12,  Resources::camera_bmp, 16, 16, WHITE);
  	}
  	else{
		m_pScreen->drawBitmap(mLeft, mBottom -12,  Resources::no_camera_bmp, 16, 16, WHITE);
  	}
}



TimerSetting::TimerSetting(Adafruit_SSD1306 *scrn, int pins[])
{
	m_pScreen = scrn;
	for(int i = 0;i < KEY_NUM;i++) mPins[i] = pins[i];
	mTimerSettingData.delaySec = 0;
	mTimerSettingData.durationSec = 0;
	mTimerSettingData.intervalSec = 0;
	mTimerSettingData.repeat = 1;
	mTimerSettingData.sound = false;	

	mSettingItems = new SettingItem*[SET_ITEM_NUM];
	for(int i = 0;i < SET_ITEM_NUM;i++){
		mSettingItems[i] = new SettingItem(scrn, ITEM_NAMES[i], i*25 + 4, 8, 25, 6);	
	}	
	mTimerArea = new TimerArea(scrn, 10, 32);
	mRepeatArea = new RepeatArea(scrn, 8, 56);
	mSoundArea = new SoundArea(scrn, 80, 56);
	mCameraArea = new CameraArea(scrn, 104, 56);

	mIsEditting = false;
	mSettingItem = SET_DELAY;
	mLongPressKey = NO_KEY;
}
TimerSetting::~TimerSetting()
{
	for(int i = 0;i < SET_ITEM_NUM;i++){
		delete mSettingItems[i];		
	}
	delete [] mSettingItems;
	delete mTimerArea;
	delete mRepeatArea;
	delete mCameraArea;
	delete mSoundArea;
}

void TimerSetting::setCameraAvailable(bool cameraAvailable)
{
	mCameraArea->setCameraAvailable(cameraAvailable);
}

void TimerSetting::setTimerData(TimerSettingData timerData)
{
	mTimerSettingData = timerData;
}
TimerSettingData TimerSetting::getTimerData(void)
{
	return mTimerSettingData;
}

void TimerSetting::showTimerSetting(bool isInit)
{
	switch(mSettingItem){
		case SET_DELAY:
			if(isInit){
				mTimerArea->setTimeSec(mTimerSettingData.delaySec);
				mTimerArea->setSettingHMS(mIsEditting? TIMER_SET_SEC:TIMER_SET_NONE);
			}
			break;
		case SET_DURATION:
			if(isInit){
				mTimerArea->setTimeSec(mTimerSettingData.durationSec);
				mTimerArea->setSettingHMS(mIsEditting? TIMER_SET_SEC:TIMER_SET_NONE);
			}
			break;
		case SET_INTERVAL:
			if(isInit){
				mTimerArea->setTimeSec(mTimerSettingData.intervalSec);
				mTimerArea->setSettingHMS(mIsEditting? TIMER_SET_SEC:TIMER_SET_NONE);
			}
			break;
		case SET_REPEAT:
			if(isInit) mRepeatArea->setRepeatCount(mTimerSettingData.repeat);
			mRepeatArea->setOn(mIsEditting);
			break;
		case SET_SOUND:
			if(isInit) mSoundArea->setSoundOn(mTimerSettingData.sound);
			mSoundArea->setOn(mIsEditting);
			break;			
	}
	
	m_pScreen->clearDisplay();
	for(int i = 0;i < SET_ITEM_NUM;i++){
		mSettingItems[i]->setOn(i == mSettingItem);
		mSettingItems[i]->show();	
	}
	mTimerArea->show();
	mRepeatArea->show();
	mSoundArea->show();
	mCameraArea->show();
	m_pScreen->display();
}
void TimerSetting::updateTimerSetting()
{
	if(mLongPressKey == NO_KEY) return;
	if(mLongPressKey == OK_KEY) return;
	unsigned long t = millis();
	if((t - mLongPressedTime) < 100) return;//100mSに一回キーを有効化する
	mLongPressedTime = t;
	if(!mIsEditting){//設定項目選択時
		switch(mLongPressKey){
			case LEFT_KEY:{
				mSettingItem = (mSettingItem + SET_ITEM_NUM -1) % SET_ITEM_NUM;
				showTimerSetting(true);
			}
			break;
			case RIGHT_KEY:{
				mSettingItem = (mSettingItem + 1) % SET_ITEM_NUM;
				showTimerSetting(true);
			}
			break;
		}
	}
	else{
		switch(mSettingItem){
			case SET_DELAY:
			case SET_DURATION:
			case SET_INTERVAL:
				switch(mLongPressKey){
					case UP_KEY:
						mTimerArea->increment();						
						break;
					case DOWN_KEY:
						mTimerArea->decrement();
						break;
					case LEFT_KEY:
						mTimerArea->shiftSettingHMSLeft();
						break;
					case RIGHT_KEY:	
						mTimerArea->shiftSettingHMSRight();
						break;
				}
				break;
			case SET_REPEAT:
				switch(mLongPressKey){
					case UP_KEY:
						mRepeatArea->increment();
						break;
					case DOWN_KEY:
						mRepeatArea->decrement();						
						break;					
				}
				break;
			case SET_SOUND:
				switch(mLongPressKey){
					case UP_KEY:
					case DOWN_KEY:
						mSoundArea->invertOn();						
						break;
				}
		}
		showTimerSetting(false);
	}
}

void TimerSetting::endEditting()
{
	switch(mSettingItem){
		case SET_DELAY:
			mTimerSettingData.delaySec = mTimerArea->getTimeSec();
			break;
		case SET_DURATION:
			mTimerSettingData.durationSec = mTimerArea->getTimeSec();
			break;
		case SET_INTERVAL:
			if(mTimerArea->getTimeSec() < 1) mTimerArea->setTimeSec(1);//Intervalは1秒以上開ける
			mTimerSettingData.intervalSec = mTimerArea->getTimeSec();
			break;
		case SET_REPEAT:
			mTimerSettingData.repeat = mRepeatArea->getRepeatCount();
			break;
		case SET_SOUND:
			mTimerSettingData.sound = mSoundArea->isSoundOn();
			break;
	}
	mIsEditting = false;
	
}

void TimerSetting::dismissTimerSetting()
{
	endEditting();
	showTimerSetting(true);
}

void TimerSetting::onKeyPressed(int pin)
{
	if(!mIsEditting){//設定項目選択時
		if(isKey(pin, OK_KEY)){
			mIsEditting = true;
			showTimerSetting(true);
			return;
		}
		if(isKey(pin, LEFT_KEY)){
			mSettingItem = (mSettingItem + SET_ITEM_NUM -1) % SET_ITEM_NUM;
			showTimerSetting(true);
			return;
		}
		if(isKey(pin, RIGHT_KEY)){
			mSettingItem = (mSettingItem + 1) % SET_ITEM_NUM;
			showTimerSetting(true);
			return;
		}
	}
	else{
		if(isKey(pin, OK_KEY)){//設定完了
			endEditting();
			showTimerSetting(true);
			return;
		}
		else{
			switch(mSettingItem){
				case SET_DELAY:
				case SET_DURATION:
				case SET_INTERVAL:
					if(isKey(pin, UP_KEY)){
						mTimerArea->increment();
					}
					else if(isKey(pin, DOWN_KEY)){
						mTimerArea->decrement();						
					}
					else if(isKey(pin, LEFT_KEY)){
						mTimerArea->shiftSettingHMSLeft();
					}
					else if(isKey(pin, RIGHT_KEY)){
						mTimerArea->shiftSettingHMSRight();
					}
					break;
				case SET_REPEAT:
					if(isKey(pin, UP_KEY)){
						mRepeatArea->increment();
					}
					else if(isKey(pin, DOWN_KEY)){
						mRepeatArea->decrement();						
					}
					break;
				case SET_SOUND:
					if(isKey(pin, UP_KEY) || isKey(pin, DOWN_KEY)){
						mSoundArea->invertOn();						
					}
					break;
			}
			showTimerSetting(false);
		}
	}
}
void TimerSetting::onKeyLongPressed(int pin)
{
	for(int i = 0;i < KEY_NUM;i++){
		if(isKey(pin, i)){
			mLongPressKey = i;
			mLongPressedTime = millis();
			return;
		}
	}
}

void TimerSetting::onKeyReleased(int pin)
{
	mLongPressKey = NO_KEY;	
}
