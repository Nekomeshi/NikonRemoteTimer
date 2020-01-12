#ifndef __SETTING_ITEM_H__
#define __SETTING_ITEM_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class SettingItem{
private:
	bool mIsOn;
	String mItemName;
	int mLeft;
	int mBottom;
	int mWidth;
	int mHeight;
	Adafruit_SSD1306 *m_pScreen;
public:
	SettingItem(Adafruit_SSD1306 *scrn, String itemName, int left, int bottom, int width, int height);
	void setOn(bool isOn);
	void show();
};


#endif
