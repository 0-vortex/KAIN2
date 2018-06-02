#include "AADSFX.H"


unsigned short aadStopAllSfx()
{
	aadPutSfxCommand(4, 0, 0, 0, 0);
	return 0;
}

unsigned short aadStopAllSlots()
{
	struct _AadSequenceSlot* slot;
	unsigned short slotNumber;

	slotNumber = 0;
	if (aadMem[0].numSlots != 0)
	{
		//loc_80054638
		for (slotNumber = 0; slotNumber < aadMem->numSlots; slotNumber++)
		{
			slot = aadMem[0].sequenceSlots[slotNumber];

			if ((slot->status & 1))
			{
				aadStopSlot(slotNumber);
			}
			//loc_80054664
			slot->sequenceNumberAssigned = 255;
		}
	}
	//loc_80054684

	return 0;
}

unsigned short /*$ra*/ aadShutdownReverb()
{
}

unsigned short /*$ra*/ aadCancelPauseSound()
{
}