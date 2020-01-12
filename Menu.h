#ifndef __MENU_H__
#define __MENU_H__
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Menu{
private:
	Adafruit_SSD1306 *m_pScreen;
	void show();
public:
	Menu(Adafruit_SSD1306 *scrn);
	virtual ~Menu();

	void startMenu(void);
	void dismissMenu(void);
	void updateMenu(void);
};



#endif
