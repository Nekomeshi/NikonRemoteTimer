#include "Menu.h"
#include <Fonts/FreeSans9pt7b.h>

Menu::Menu(Adafruit_SSD1306 *scrn)
{
	m_pScreen = scrn;
}
Menu::~Menu()
{
	
}

void Menu::show()
{
	m_pScreen->clearDisplay();
  	m_pScreen->setTextWrap(false);
  	m_pScreen->setFont(&FreeSans9pt7b);
  	m_pScreen->setTextSize(1);  	
  	m_pScreen->setTextColor(WHITE);
  	
  	m_pScreen->setCursor(0,24);
  	m_pScreen->print("Not Implemented Yet");
  	m_pScreen->setCursor(0,45);
  	m_pScreen->print("Push menu button");
	m_pScreen->display();
	
}

void Menu::startMenu(void)
{
	show();
}
void Menu::dismissMenu(void)
{
	
}
void Menu::updateMenu(void)
{
	
}
