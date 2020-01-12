#include "CaptureCtrl.h"

#define BUZZ_DURATION 100 //mS
#define BUZZER_TONE	2093	//ドの音程

CaptureCtrl::CaptureCtrl(Nikon *cam, Buzzer *buzz, int idleLEDPin, int busyLEDPin)
{
	m_pCam = cam;
	m_pBuzzer = buzz;
	mUseBuzzer = false;
	mIdleLEDPin = idleLEDPin;
	mBusyLEDPin = busyLEDPin;
	digitalWrite(mIdleLEDPin, HIGH);
	digitalWrite(mBusyLEDPin, LOW);
}
CaptureCtrl::~CaptureCtrl()
{
	
}
void CaptureCtrl::startCapture(bool useAF)
{
	mCapStartTime = millis();
	mLastTickTimeSec = 0;
	
	digitalWrite(mIdleLEDPin, LOW);
	digitalWrite(mBusyLEDPin, HIGH);
	m_pCam->StartCapture(useAF);
}
void CaptureCtrl::stopCapture()
{
	if(m_pBuzzer != NULL && mUseBuzzer) m_pBuzzer->stopBuzz();
	m_pCam->TerminateCapture();	
	digitalWrite(mIdleLEDPin, HIGH);
	digitalWrite(mBusyLEDPin, LOW);
}

void CaptureCtrl::updateCapture()
{
	int tick = (millis() - mCapStartTime)/1000;
	if(tick > mLastTickTimeSec){
		mLastTickTimeSec = tick;
		if(onTickCB != NULL) (*onTickCB)(tick);
		if(m_pBuzzer != NULL && mUseBuzzer) m_pBuzzer->startBuzz(BUZZER_TONE, BUZZ_DURATION);
	}
	if(m_pBuzzer != NULL && mUseBuzzer) m_pBuzzer->updateBuzz();
}
	
void CaptureCtrl::useBuzzer(bool useBuzzer)
{
	mUseBuzzer = useBuzzer;
}
void CaptureCtrl::setTickCB(void (*cb)(int))
{
	onTickCB = cb;
}
