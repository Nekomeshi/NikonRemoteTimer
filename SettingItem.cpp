#include "SettingItem.h"
#include "ScreenInfo.h"
#include <Fonts/TomThumb.h>

SettingItem::SettingItem(Adafruit_SSD1306 *scrn, String itemName, int left, int bottom, int width, int height)
{
	m_pScreen = scrn;
	mIsOn = false;
	mItemName = itemName;
	mLeft = left;
	mBottom = bottom;
	mHeight = height;
	mWidth = width;
}

void SettingItem::setOn(bool isOn)
{
	mIsOn = isOn;
}
void SettingItem::show()
{	
  	m_pScreen->setTextWrap(false);
  	m_pScreen->setFont(&TomThumb);
  	m_pScreen->setTextSize(1);  	
  	m_pScreen->setTextColor(WHITE);
  	m_pScreen->setCursor(mLeft,mBottom);
  	m_pScreen->println(mItemName);

  	if(mIsOn){
  		drawFrame(m_pScreen, mLeft-3, mBottom - mHeight-2, mWidth-1, mHeight+4);
  	}
}
