#include "KeyManager.h"
#include "esp32-hal-log.h"
#include "freertos/task.h"

portTickType Delay10 = 10 / portTICK_RATE_MS; //freeRTOS 用の遅延時間定義

#define LONG_PRESS_THRESS 50 //*Delay10mS

KeyManager::KeyManager(int *pinList, int pinNum)
{
	mPinNum = pinNum;
	if(pinNum == 0){
		mPinList = NULL;
	}
	else{
		mPinList = new int[pinNum];
		mIsLongPressed = new bool[pinNum];
		for(int i = 0;i < pinNum;i++){
			mPinList[i] = pinList[i];
			mIsLongPressed[i] = false;
		}
	}
	onKeyDownCB = NULL;
	onKeyPressedCB = NULL;
	onKeyLongPressedCB = NULL;
	onKeyUpCB = NULL;
	mKeyListeningRunning = false;
}

KeyManager::~KeyManager()
{
	if(mPinList != NULL) delete [] mPinList;	
}

void KeyManager::stopListiningKey()
{
	mKeyListeningRunning = false;
}

void KeyManager::startListiningKey()
{
	mKeyListeningRunning = true;
	xTaskCreatePinnedToCore(keyListeningTask, "keyListeningTask", 4096,  this, 1, NULL, 1);
}

void KeyManager::keyListeningTask(void *pvParameters)
{
	KeyManager *manager = (KeyManager *)pvParameters;
	
	while(manager->mKeyListeningRunning){
		int pin = -1;
		for(int i = 0;i < manager->mPinNum;i++){
			if(digitalRead(manager->mPinList[i]) == LOW){
				pin = manager->mPinList[i];
				if(manager->onKeyDownCB != NULL){
					(*(manager->onKeyDownCB))(pin);
				}

				break;
			}
		}
		if(pin < 0){
			vTaskDelay(Delay10);
			continue;
		}
		int longPressTime = 0;
		while(digitalRead(pin)==LOW) {
			if(longPressTime >= 50) break;//長押し確定
			longPressTime++;
			vTaskDelay(Delay10);
		}
		if(longPressTime < 50){//短オシ
			if(manager->onKeyUpCB != NULL){
				(*(manager->onKeyUpCB))(pin, false);
			}
			if(manager->onKeyPressedCB != NULL){
				(*(manager->onKeyPressedCB))(pin);
			}
			continue;
		}
		if(manager->onKeyLongPressedCB != NULL){
			(*(manager->onKeyLongPressedCB))(pin);			
		}
		while(digitalRead(pin)==LOW) {
			vTaskDelay(Delay10);
		}
		if(manager->onKeyUpCB != NULL){
			(*(manager->onKeyUpCB))(pin, true);
		}
		vTaskDelay(Delay10);
	}
}
void KeyManager::setOnKeyDownCB(void (*cb)(int))
{
	onKeyDownCB = cb;
}
void KeyManager::setOnKeyPressedCB(void (*cb)(int))
{
	onKeyPressedCB = cb;
}
void KeyManager::setOnKeyLongPressedCB(void (*cb)(int))
{
	onKeyLongPressedCB = cb;
}
void KeyManager::setOnKeyUpCB(void (*cb)(int, bool))
{
	onKeyUpCB = cb;
}
