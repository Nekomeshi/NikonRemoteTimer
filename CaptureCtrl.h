#ifndef __CAPTURE_CTRL_H__
#define __CAPTURE_CTRL_H__

#include "Buzzer.h"
#include "CameraCtrl.h"

class CaptureCtrl{
private:
	Nikon *m_pCam;
	Buzzer *m_pBuzzer;	
	void (*onTickCB)(int timeSec);
	unsigned long mCapStartTime;
	int mLastTickTimeSec;
	int mIdleLEDPin;
	int mBusyLEDPin;
	bool mUseBuzzer;
public:
	CaptureCtrl(Nikon *cam, Buzzer *buzz, int idleLEDPin, int busyLEDPin);
	virtual ~CaptureCtrl();
	void startCapture(bool useAF);
	void stopCapture();
	void updateCapture();
	
	void useBuzzer(bool useBuzzer);
	void setTickCB(void (*cb)(int));
};

#endif
