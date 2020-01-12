#include "SingleShoot.h"
#include <Fonts/FreeSans9pt7b.h>

SingleShoot::SingleShoot(Adafruit_SSD1306 *scrn, CaptureCtrl *cap)
{
	m_pScreen = scrn;
	m_pCaptureCtrl = cap;
	mMakeSound = false;
	m_pTimerArea = new TimerArea(scrn, 10, 54);
}
SingleShoot::~SingleShoot()
{
	delete m_pTimerArea;	
}

void SingleShoot::makeSound(bool makeSound)
{
	mMakeSound = makeSound;
}
void SingleShoot::show()
{
	m_pScreen->clearDisplay();
  	m_pScreen->setTextWrap(false);
  	m_pScreen->setFont(&FreeSans9pt7b);
  	m_pScreen->setTextSize(1);  	
  	m_pScreen->setTextColor(WHITE);
  	
  	m_pScreen->setCursor(10,24);
  	m_pScreen->print("Elapsed:");
	m_pTimerArea->show();	
	m_pScreen->display();
}
void SingleShoot::startCapture(bool useAF)
{
 	mStartTimeMS = millis();
	mLastTickTime = 0;
	m_pTimerArea->setTimeSec(mLastTickTime);
	m_pCaptureCtrl->useBuzzer(mMakeSound);
	m_pCaptureCtrl->startCapture(useAF);
	show();
}
void SingleShoot::stopCapture()
{
	m_pCaptureCtrl->stopCapture();
}
void SingleShoot::updateCapture()
{	
	m_pCaptureCtrl->updateCapture();
	unsigned long t = (millis()- mStartTimeMS)/1000 ;
	if( t > mLastTickTime){
		mLastTickTime = t;
		m_pTimerArea->setTimeSec(mLastTickTime);
		show();
	}
}
