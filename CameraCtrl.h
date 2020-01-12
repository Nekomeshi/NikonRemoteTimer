#ifndef __CAMERA_CTRL_H__
#define __CAMERA_CTRL_H__
#include <Arduino.h>
#include <ptp.h>
#include <ptpdebug.h>
#include <nikon.h>
#include <usbhub.h>
#include <eoseventdump.h>

class CamStateHandlers : public PTPStateHandlers
{
private:
      enum CamStates { stInitial, stDisconnected, stConnected };
      CamStates stateConnected;
public:

      CamStateHandlers();

      virtual void OnDeviceDisconnectedState(PTP *ptp);
      virtual void OnDeviceInitializedState(PTP *ptp);

      bool IsCameraConnected();
};

class Nikon : public NikonDSLR
{
public:
    bool        bPollEnabled;   // Enables or disables camera poll
    bool        bLVEnabled;
    uint32_t    nStep;
    uint32_t	mTerminateParam0;

    Nikon(USB *pusb, PTPStateHandlers *pstates);
	uint16_t StartCapture(bool useAF);
	uint16_t TerminateCapture(void);
	uint16_t StartLiveView(void);
	uint16_t EndLiveView(void);
};
#endif
