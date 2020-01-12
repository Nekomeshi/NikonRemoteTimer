#ifndef __SCREEN_INFO_H__
#define __SCREEN_INFO_H__

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define LINE_POS(p) ((p)*SCREEN_HEIGHT/4 + 12)

extern void drawFrame(Adafruit_SSD1306 *scrn, int l, int t, int w, int h);

class Resources{
public:
	Resources();
	~Resources();
	static const unsigned char PROGMEM up_bmp[32];
	static const unsigned char PROGMEM up_inv_bmp[32];
	static const unsigned char PROGMEM down_bmp[32];
	static const unsigned char PROGMEM down_inv_bmp[32];
	static const unsigned char PROGMEM ok_bmp[32];
	static const unsigned char PROGMEM ok_inv_bmp[32];
	static const unsigned char PROGMEM cancel_bmp[32];
	static const unsigned char PROGMEM cancel_inv_bmp[32];

	static const unsigned char PROGMEM bt_bmp[32];
	static const unsigned char PROGMEM bt_connected_bmp[32];
	static const unsigned char PROGMEM bt_disabled_bmp[32];	
	static const unsigned char PROGMEM note_bmp[32];
//	static const unsigned char PROGMEM note_inv_bmp[32];

	static const unsigned char PROGMEM no_note_bmp[32];

	static const unsigned char PROGMEM camera_bmp[32];
//	static const unsigned char PROGMEM camera_inv_bmp[32];
	static const unsigned char PROGMEM no_camera_bmp[32];
//	static const unsigned char PROGMEM no_camera_inv_bmp[32];
};
#endif
