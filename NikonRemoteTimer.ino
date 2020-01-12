#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Fonts/TomThumb.h>
#include <Fonts/Org_01.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/Picopixel.h>
#include <Fonts/FreeSansOblique9pt7b.h>

#include "esp32-hal-log.h"
#include "freertos/task.h"

#include "Buzzer.h"
#include "CameraCtrl.h"
#include "TimerSetting.h"
#include "KeyManager.h"
#include "CaptureCtrl.h"
#include "SingleShoot.h"
#include "TimerShoot.h"
#include "Menu.h"

#include "Utils.h"

#define PIN_SW_MENU			32
#define PIN_SW_R 			12
#define PIN_SW_U			26
#define PIN_SW_OK			14
#define PIN_SW_D			13
#define PIN_SW_L			27
#define PIN_SW_SHOOT		25//タイマー撮影開始ボタン
#define PIN_BUZZER			15
#define PIN_LED_IDLE		16
#define PIN_LED_SHOOT		4
#define PIN_SW_ONE_SHOOT	33//単発撮影開始スイッチ

#define BUZZER_TONE	2093	//ドの音程

//カメラ定義
CamStateHandlers    CamStateHandle;
USB                 Usb;
USBHub              Hub1(&Usb);
Nikon               Nik(&Usb, &CamStateHandle);

//ブザー
Buzzer				mBuzzer(PIN_BUZZER);


//OLED定義
#define OLED_RESET -1  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

TimerSetting 	*g_pTimerSetting;
KeyManager 		*g_pKeyManager;
CaptureCtrl		*g_pCaptureCtrl;
SingleShoot		*g_pSingleShoot;
TimerShoot		*g_pTimerShoot; 
Menu			*g_pMenu;


#define RUNNING_STATE_IDLE  			0
#define RUNNING_STATE_RUNNING_TIMER  	1
#define RUNNING_STATE_ONE_SHOOT 	 	2
#define RUNNING_STATE_MENU 			 	3

#define RUNNING_MODE_TIMER				0
#define RUNNING_MODE_BLE				1

int gRunningState = RUNNING_STATE_IDLE;
int gRunningMode = RUNNING_MODE_TIMER;

bool gIsConnected = false;


SemaphoreHandle_t gXMutex = NULL;
static const TickType_t xTicksToWait = 1000U; // [ms]

void CamStateHandlers::OnDeviceDisconnectedState(PTP *ptp)
{
    PTPTRACE("Disconnected\r\n");
    if (stateConnected == stConnected || stateConnected == stInitial)
    {
        stateConnected = stDisconnected;
        E_Notify(PSTR("\r\nDevice disconnected.\r\n"),0x80);
    }
}

void CamStateHandlers::OnDeviceInitializedState(PTP *ptp)
{
    if (stateConnected == stDisconnected || stateConnected == stInitial)
    {
        stateConnected = stConnected;
        E_Notify(PSTR("\r\nDevice connected.\r\n"),0x80);
    }    
}


void setupScreen(){
  	OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  	OLED.clearDisplay();

/*



  	OLED.setFont(&TomThumb);
  
  	//Add stuff into the 'display buffer'
  	OLED.setTextWrap(false);
  	OLED.setTextSize(1);
  	
  	OLED.setTextColor(WHITE);
//  	OLED.setCursor(0,12);
//  	OLED.setFont(&TomThumb);
//  	OLED.println("0123456789012345678901234567890123456789");

//  	OLED.setTextColor(WHITE);
  //	OLED.setCursor(64,12);
  	//OLED.setFont(&FreeSans9pt7b);
  	//OLED.println("0123456789abcdef");

  	
//  	OLED.setCursor(0,16+12);
//  	OLED.setFont(&Org_01);
//  	OLED.println("0123456789abcdef");
//  	OLED.setCursor(0,32+12);
//  	OLED.setFont(&FreeMono9pt7b);
 // 	OLED.println("fedcba987654321");
 // 	OLED.setCursor(0,48+12);
//  	OLED.setFont(&Picopixel);
//  	OLED.println("fedcba987654321");

//  	OLED.setCursor(64,48+12);
//  	OLED.setFont(&FreeSansOblique9pt7b);
//  	OLED.println("fedcba987654321");

//  	OLED.display(); //output 'display buffer' to screen  
*/
/*
  	pMenu = new Menu(&OLED, menuCB);  
  	pScreen = new MainScreen(&OLED);
  	pScreen->init();

	pScreen->setLowSpeed(gLowSpeed);
	pScreen->setHighSpeed(gHighSpeed);
	pScreen->setVoltage(gVoltage.getValue());
	pScreen->setPoleDirection(gIsNorth);
	OLED.brightness(gBrightness);
	pScreen->showMainScreen();
	*/
}
void onKeyDown(int pin)
{
	Serial.println(__FUNCTION__);
	Serial.println(pin);

	BaseType_t 	xStatus = xSemaphoreTake(gXMutex, xTicksToWait);	
    if(gIsConnected){
    	switch(gRunningMode){
    		case RUNNING_MODE_TIMER:{
				switch(gRunningState){
					case RUNNING_STATE_IDLE:
						if(pin == PIN_SW_SHOOT){//タイマースタート						
							dismissTimerSetting();
							gRunningState = RUNNING_STATE_RUNNING_TIMER;
							startTimerTask();
						}
						else if(pin == PIN_SW_ONE_SHOOT){//one shot撮影スタート
							dismissTimerSetting();
							gRunningState = RUNNING_STATE_ONE_SHOOT;
							startOneShootTask();
						}
						break;
					case RUNNING_STATE_RUNNING_TIMER://タイマー停止
						if(pin == PIN_SW_SHOOT){
							stopTimerTask();
							gRunningState = RUNNING_STATE_IDLE;
							startTimerSetting();						}
						break;
					case RUNNING_STATE_ONE_SHOOT:
						break;
					case RUNNING_STATE_MENU:
						break;
				}
    		}
    		break;
    		case RUNNING_MODE_BLE:{
				//ToDo:    			
    		}
    		break;    		
    	}
    }
    else{
    	switch(gRunningMode){
    		case RUNNING_MODE_TIMER:{
    			//nothing to do
    		}
    		break;
    		case RUNNING_MODE_BLE:{
				//ToDo:    			
    		}
    		break;
    	}
    }

   	xSemaphoreGive(gXMutex);
}

void onKeyPressed(int pin)
{
	Serial.print(__FUNCTION__);
	Serial.println(pin);

	BaseType_t 	xStatus = xSemaphoreTake(gXMutex, xTicksToWait);
	if(xStatus != pdTRUE) Serial.println("Can not take Semaphore in OnKeyPressed");

   	switch(gRunningMode){
   		case RUNNING_MODE_TIMER:{
			switch(gRunningState){
				case RUNNING_STATE_IDLE:
					if(pin == PIN_SW_MENU){//メニュー表示
						dismissTimerSetting();
						gRunningState = RUNNING_STATE_MENU;
						startMenu();
					}
					else{//タイマー設定を変更
						g_pTimerSetting->onKeyPressed(pin);
					}
					break;
				case RUNNING_STATE_RUNNING_TIMER:
					break;
				case RUNNING_STATE_ONE_SHOOT:
					break;
				case RUNNING_STATE_MENU:
					if(pin == PIN_SW_MENU){//メニューを閉じる
						dismissMenu();
						gRunningState = RUNNING_STATE_IDLE;
						startTimerSetting();
					}
					else{
//						updateMenu();メニューにpinを送る
					}
					break;
			}
   		}
   		break;
   		case RUNNING_MODE_BLE:{
			//ToDo:    			
   		}
   		break;
   	}	
   	xSemaphoreGive(gXMutex);
}
void onKeyLongPressed(int pin)
{
	Serial.print(__FUNCTION__);
	Serial.println(pin);

	BaseType_t 	xStatus = xSemaphoreTake(gXMutex, xTicksToWait);
	if(xStatus != pdTRUE) Serial.println("Can not take Semaphore in onKeyLongPressed");

	if(gRunningMode == RUNNING_MODE_TIMER &&
		gRunningState == RUNNING_STATE_IDLE){
		g_pTimerSetting->onKeyLongPressed(pin);
	}
   	xSemaphoreGive(gXMutex);
}

void onKeyUp(int pin, bool isLongPress)
{
	Serial.print(__FUNCTION__);
	Serial.print(" ");
	Serial.print(isLongPress );
	Serial.print(" ");
	Serial.println(pin);

	BaseType_t 	xStatus = xSemaphoreTake(gXMutex, xTicksToWait);	
	if(xStatus != pdTRUE) Serial.println("Can not take Semaphore in onKeyReleased");
   	switch(gRunningMode){
   		case RUNNING_MODE_TIMER:{
			switch(gRunningState){
				case RUNNING_STATE_IDLE:
					if(isLongPress)	g_pTimerSetting->onKeyReleased(pin);
					break;
				case RUNNING_STATE_ONE_SHOOT:
					stopOneShootTask();
					gRunningState = RUNNING_STATE_IDLE;
					startTimerSetting();
					break;
				default:
					break;
			}
	   		break;
   			case RUNNING_MODE_BLE:{
				//ToDo:    			
   			}
   			break;
		}
	}
	xSemaphoreGive(gXMutex);
}

void onCaptureTick(int sec){
	Serial.print("Tick:");
	Serial.println(sec);
}

void onTimerEnd(bool isCompleted){
	Serial.print(__FUNCTION__);
	Serial.println(isCompleted);
	if(isCompleted){
		gRunningState = RUNNING_STATE_IDLE;
		startTimerSetting();
	}
}

void setupPins(){
  	pinMode(PIN_SW_MENU, INPUT_PULLUP);
  	pinMode(PIN_SW_R, INPUT_PULLUP);
  	pinMode(PIN_SW_U, INPUT_PULLUP);
  	pinMode(PIN_SW_OK, INPUT_PULLUP);
  	pinMode(PIN_SW_D, INPUT_PULLUP);
  	pinMode(PIN_SW_L, INPUT_PULLUP);
  	pinMode(PIN_SW_ONE_SHOOT, INPUT_PULLUP);
  	pinMode(PIN_SW_SHOOT, INPUT_PULLUP);
 	
  	pinMode(PIN_LED_IDLE, OUTPUT);
  	pinMode(PIN_LED_SHOOT, OUTPUT);

	int keys[8] = {PIN_SW_MENU, PIN_SW_R , PIN_SW_L, PIN_SW_U, PIN_SW_D, PIN_SW_OK, PIN_SW_SHOOT, PIN_SW_ONE_SHOOT};

  	g_pKeyManager = new KeyManager(keys, 8);
}


void setup() {
  	// put your setup code here, to run once:
    Serial.begin( 115200 );
    Serial.println("Start");

    if (Usb.Init() == -1){
    	Serial.println("OSC did not start.");
    }
    
    
	gXMutex = xSemaphoreCreateMutex();
	
	gRunningState = RUNNING_STATE_IDLE;

	setupPins();
	setupScreen();

	int keys[KEY_NUM] = {PIN_SW_U, PIN_SW_D, PIN_SW_L, PIN_SW_R, PIN_SW_OK, PIN_SW_MENU};
	g_pTimerSetting = new TimerSetting(&OLED, keys);
	g_pCaptureCtrl = new CaptureCtrl(&Nik, &mBuzzer, PIN_LED_IDLE, PIN_LED_SHOOT);
    g_pCaptureCtrl->useBuzzer(false);
    g_pCaptureCtrl->setTickCB(onCaptureTick);

	g_pSingleShoot = new SingleShoot(&OLED, g_pCaptureCtrl);

	g_pTimerShoot = new TimerShoot(&OLED, g_pCaptureCtrl);
	g_pTimerShoot->setOnTimerEnd(onTimerEnd);

	g_pMenu = new Menu(&OLED);
		
  	g_pKeyManager->setOnKeyDownCB(onKeyDown);
  	g_pKeyManager->setOnKeyPressedCB(onKeyPressed);
  	g_pKeyManager->setOnKeyLongPressedCB(onKeyLongPressed);
  	g_pKeyManager->setOnKeyUpCB(onKeyUp);
  	g_pKeyManager->startListiningKey();

	startTimerSetting();
    delay( 200 );
}

void OnConnected()
{
	switch(gRunningMode){
		case RUNNING_MODE_TIMER:{
			switch(gRunningState){
				case RUNNING_STATE_IDLE:
					startTimerSetting();
					break;
				case RUNNING_STATE_RUNNING_TIMER://発生しない
					break;
				case RUNNING_STATE_ONE_SHOOT://発生しない
					break;
				case RUNNING_STATE_MENU://発生しない
					break;
			}
		}
		break;
		case RUNNING_MODE_BLE:{
			//To Do:
		}
		break;
	}	
}

void OnDisconnected()
{
	switch(gRunningMode){
		case RUNNING_MODE_TIMER:{
			switch(gRunningState){
				case RUNNING_STATE_IDLE:
					break;
				case RUNNING_STATE_RUNNING_TIMER:
					stopTimerTask();
					break;
				case RUNNING_STATE_ONE_SHOOT:
					stopOneShootTask();
					break;
				case RUNNING_STATE_MENU:
					dismissMenu();
					break;
			}
			gRunningState = RUNNING_STATE_IDLE;
			startTimerSetting();
		}
		break;
		case RUNNING_MODE_BLE:{
			//To Do:
		}
		break;
	}
}

void startTimerSetting()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);
#endif
	g_pTimerSetting->setCameraAvailable(gIsConnected);
	g_pTimerSetting->showTimerSetting(true);
}
void updateTimerSetting()
{
//	Serial.println(__FUNCTION__);
	g_pTimerSetting->updateTimerSetting();	
}
void dismissTimerSetting()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);	
#endif
	g_pTimerSetting->dismissTimerSetting();	
}
	
void startTimerTask()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);
#endif

	g_pTimerShoot->setTimerData(g_pTimerSetting->getTimerData());
	g_pTimerShoot->startTimer(false);
}
void updateTimerTask()
{
//	Serial.println(__FUNCTION__);
	g_pTimerShoot->updateTimer();
}
void stopTimerTask()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);
#endif
	g_pTimerShoot->stopTimer();
}
void startOneShootTask()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);
#endif
	g_pSingleShoot->makeSound(g_pTimerSetting->getTimerData().sound);
	g_pSingleShoot->startCapture(false);
}
void updateOneShootTask()
{
//	Serial.println(__FUNCTION__);
	g_pSingleShoot->updateCapture();
}
void stopOneShootTask()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);
#endif
	g_pSingleShoot->stopCapture();
}

void startMenu()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);
#endif
	g_pMenu->startMenu();
}
void updateMenu()
{
//	Serial.println(__FUNCTION__);
	g_pMenu->updateMenu();
}
void dismissMenu()
{
#ifdef MY_DEBUG
	Serial.println(__FUNCTION__);
#endif
	g_pMenu->dismissMenu();
}

//int a = 0;
void loop() {
  	// put your main code here, to run repeatedly:
    Usb.Task();
/*	
    	if(a == 500){
    		Nik.StartCapture(false);
    		mBuzzer.startBuzz(BUZZER_TONE, 100);
    	}
    	else if(a == 1000){
    		Nik.TerminateCapture();
    	}
    	else if(a == 1500){
    		Nik.StartCapture(false);    
    		mBuzzer.startBuzz(BUZZER_TONE, 500);		
    	}
    	else if(a == 2000){
    		
    		mBuzzer.stopBuzz();
	mBuzzer.updateBuzz();
    		Nik.TerminateCapture();
    	}
	a++;
	
	delay(10);
	return;
    */
   	BaseType_t 	xStatus = xSemaphoreTake(gXMutex, xTicksToWait);
	if(xStatus != pdTRUE) Serial.println("Can not take Semaphore in loop");
	
    if(CamStateHandle.IsCameraConnected()){
    	if(!gIsConnected){
    		gIsConnected = true;
    		OnConnected();
    	}
    	switch(gRunningMode){
    		case RUNNING_MODE_TIMER:{
				switch(gRunningState){
					case RUNNING_STATE_IDLE:
						updateTimerSetting();
						break;
					case RUNNING_STATE_RUNNING_TIMER:
						updateTimerTask();
						break;
					case RUNNING_STATE_ONE_SHOOT:
						updateOneShootTask();
						break;
					case RUNNING_STATE_MENU:
						updateMenu();
						break;
				}
    		}
    		break;
    		case RUNNING_MODE_BLE:{
				//ToDo:    			
    		}
    		break;
    		
    	}
    }
    else{
    	if(gIsConnected){
    		gIsConnected = false;
    		OnDisconnected();
    	}
    	switch(gRunningMode){
    		case RUNNING_MODE_TIMER:{
				switch(gRunningState){
					case RUNNING_STATE_IDLE:
						updateTimerSetting();
						break;
					case RUNNING_STATE_RUNNING_TIMER://発生しない
						break;
					case RUNNING_STATE_ONE_SHOOT://発生しない
						break;
					case RUNNING_STATE_MENU:
						updateMenu();
						break;
				}
    		}
    		break;
    		case RUNNING_MODE_BLE:{
				//ToDo:    			
    		}
    		break;
    	}
    }
   	xSemaphoreGive(gXMutex);

    delay( 10 );
}
