#include "AADSFX.H"


unsigned short aadStopAllSfx()
{
	aadPutSfxCommand(4, 0, 0, 0, 0);
	return 0;
}

unsigned short aadStopAllSlots()
{
	return 0;
}

unsigned short /*$ra*/ aadShutdownReverb()
{
}

unsigned short /*$ra*/ aadCancelPauseSound()
{
}