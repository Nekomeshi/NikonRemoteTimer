#ifndef __KEY_MANAGER_H__
#define __KEY_MANAGER_H__
#include <Arduino.h>



class KeyManager{

public:
	KeyManager(int *pinList, int pinNum);
	virtual ~KeyManager();
	void setOnKeyDownCB(void (*cb)(int));
	void setOnKeyPressedCB(void (*cb)(int));
	void setOnKeyLongPressedCB(void (*cb)(int));
	void setOnKeyUpCB(void (*cb)(int, bool));
	void startListiningKey();
	void stopListiningKey();

	void (*onKeyDownCB)(int pin);
	void (*onKeyPressedCB)(int pin);
	void (*onKeyLongPressedCB)(int pin);
	void (*onKeyUpCB)(int pin, bool isLongPress);
	bool mKeyListeningRunning;
	int mPinNum;
	int *mPinList;

private:
	bool *mIsLongPressed;		
	static void keyListeningTask(void *pvParameters);
};


#endif
