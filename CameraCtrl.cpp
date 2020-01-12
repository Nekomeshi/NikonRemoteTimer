#include "CameraCtrl.h"


CamStateHandlers::CamStateHandlers() : stateConnected(stInitial)
{
}
bool CamStateHandlers::IsCameraConnected(){
	return stateConnected == stConnected;
}


#define NK_OC_TerminateCapture						0x920C
#define NK_OC_InitiateCaptureRecInMedia				0x9207

Nikon::Nikon(USB *pusb, PTPStateHandlers *pstates)  : NikonDSLR(pusb, pstates)
{
   	mTerminateParam0 = 0x00000000;
};
uint16_t Nikon::StartCapture(bool useAF){
	uint32_t	params[2];
	params[0]	= (uint32_t)useAF?0xFFFFFFFE:0xFFFFFFFF;
	params[1]	= (uint32_t)0x00000000;
	uint16_t ret = Operation(NK_OC_InitiateCaptureRecInMedia, 2, params);	
	Serial.print("StartCapture:0x");
	Serial.println(ret, HEX);
	return ret;
}
uint16_t Nikon::TerminateCapture(void){
	uint16_t 	ret = PTP_RC_OK;
	uint32_t	params[2];
	params[1]	= (uint32_t)0x00000000;
	if(mTerminateParam0 != 0x00000000){
		params[0] = mTerminateParam0;
		ret = Operation(NK_OC_TerminateCapture, 2, params);
	}
	else{
		for(uint32_t i = 0x00;i < 0xff;i++){//param0はZ50のPTPコマンド仕様書上ではReserved(0)となっているが、実際は0x01で動作する。
										//何が正しいかわからないため順に送る
			params[0]	= i;
			uint16_t ret = Operation(NK_OC_TerminateCapture, 2, params);
			if(ret != PTP_RC_ParameterNotSupported){//パラメータは正しかったらしい
				if(ret == PTP_RC_OK) mTerminateParam0 = i;
				break;
			}
		}
	}
	Serial.print("TerminateCapture:0x");
	Serial.println(ret, HEX);
	return ret;
}
uint16_t Nikon::StartLiveView(void){
	return Operation(PTP_OC_NIKON_StartLiveView, 0, NULL);
}
uint16_t Nikon::EndLiveView(void){
	return Operation(PTP_OC_NIKON_EndLiveView, 0, NULL);	
}
