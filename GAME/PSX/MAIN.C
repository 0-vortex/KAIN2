#include "G2TYPES.H"

#include "LOAD3D.H"
#include "MAING2.H"
#include "MAINVM.H"
#include "MEMPACK.H"

#include <LIBETC.H>
#include <LIBGPU.H>
#include <LIBAPI.H>
#include <LIBGPU.H>
#include <STDDEF.H>

void DoCinematicStuff(struct GameTracker* gameTracker, struct MainTracker* mainTracker)
{
	return;
}

void InitMainTracker(struct MainTracker* mainTracker)
{
	mainTracker->mainState = 1;
	mainTracker->previousState = 0;
	mainTracker->done = 0;
}


char* FindTextInLine(char* search_match, char* search_str)
{
	char* match_pos = search_match;

	if (*search_str == 0)
	{
		return NULL;
	}

	if (*search_str == 0xA)
	{
		return NULL;
	}

	while (*match_pos != 0xA)
	{
		if (*search_str == 0xD)
		{
			return NULL;
		}

		if ((*search_str++ | 0x20) == (*match_pos | 0x20))
		{
			match_pos++;
		}
		else
		{
			match_pos = search_match;
		}

		if (*match_pos == 0)
		{
			return search_str;
		}

		if (*search_str == 0)
		{
			return NULL;
		}
	}
}

void ExtractWorldName(char* worldName, char* levelName)
{
	if (*levelName != '-')
	{
		while (*levelName != '-')
		{
			if ((*levelName = 0x41) > 0x19 && (*levelName - 0x61) > 0x19)
			{
				break;
			}

			*worldName++ = *levelName++;
		}
	}

	*worldName = 0;
}

/*
* Offset 0x80038BD4
* C:\kain2\game\PSX\MAIN.C (line 130)
* Stack frame base $sp, size 0
*/
void /*$ra*/ ExtractLevelNum(char *levelNum /*$a0*/, char *levelName /*$a1*/)
{
}
/*
* Offset 0x80038C40
* C:\kain2\game\PSX\MAIN.C (line 220)
* Stack frame base $sp, size 104
* Saved registers at offset -8: s0 s1 s2 s3 ra
*/
void /*$ra*/ ProcessArgs(char *argFileName /*$a0*/, char *baseAreaName /*$s3*/, struct GameTracker *gameTracker /*$s2*/)
{ // line 1, offset 0x80038c40
	char levelNum[32]; // stack offset -88
	char worldName[32]; // stack offset -56
	long *argData; // $s1
} // line 188, offset 0x80038d98

void ClearDisplay()
{
	PutDrawEnv(&draw[gameTrackerX.dispPage]);
	DrawPrim(&clearRect);
	DrawSync(0);
	PutDispEnv(disp[gameTrackerX.dispPage]);
	SetDispMask(1);
}
/*
* Offset 0x80038E38
* C:\kain2\game\PSX\MAIN.C (line 420)
* Stack frame base $sp, size 56
* Saved registers at offset -8: s0 s1 s2 s3 ra
*/
void /*$ra*/ InitDisplay(int w /*$s2*/, int h /*$s0*/)
{ // line 1, offset 0x80038e38
	RECT r; // stack offset -32
} // line 16, offset 0x80038f0c

void StartTimer()
{
	EnterCriticalSection();
	__timerEvent = OpenEvent(0xF2000000, 2, 0x1000, TimerTick);
	EnableEvent(__timerEvent);
	SetRCnt(0xF2000000, 0xFFFF, 0x1001);
	StartRCnt(0xF2000000);
	ExitCriticalSection();
}

void /*$ra*/ VblTick()
{
}
/*
* Offset 0x800390E0
* C:\kain2\game\PSX\MAIN.C (line 525)
* Stack frame base $sp, size 24
* Saved registers at offset -8: ra
*/
void /*$ra*/ DrawCallback()
{
}
/*
* Offset 0x80039138
* C:\kain2\game\PSX\MAIN.C (line 575)
* Stack frame base $sp, size 80
* Saved registers at offset -4: s0 s1 s2 s3 s4 ra
*/
void /*$ra*/ FadeOutSayingLoading(struct GameTracker *gameTracker /*$s0*/)
{ // line 1, offset 0x80039138
	struct POLY_F4_SEMITRANS *transPrim; // $s2
	unsigned long **drawot; // $s3
	long fadeTime; // $s1
} // line 29, offset 0x80039288

void CheckForDevStation()
{
	long* a1;
	long* a2;

	a1 = (long*)0x80180000;
	a2 = (long*)0x80380000;

	*a1 = 0;
	*a2 = 0x12345678;

	if (*a1 == *a2)
	{
		devstation = 0;
	}
	else
	{
		devstation = 1;
	}
}

void MAIN_ShowLoadingScreen()
{
	long* loadingScreen;

	VSync(0);

	loadingScreen = LOAD_ReadFile("\\kain2\\game\\psx\\loading.tim", 0xB);
	if (loadingScreen != NULL)
	{
		LOAD_LoadTIM2(loadingScreen, 0, gameTrackerX.dispPage << 8, 512, 256);
		MEMPACK_Free((char*)loadingScreen);
	}
}

  /*
  * Offset 0x8003936C
  * C:\kain2\game\PSX\MAIN.C (line 658)
  * Stack frame base $sp, size 24
  * Saved registers at offset -8: ra
  */
long * /*$ra*/ MAIN_LoadTim(char *name /*$a0*/)
{ // line 1, offset 0x8003936c
} // line 1, offset 0x8003936c
  /*
  * Offset 0x8003938C
  * C:\kain2\game\PSX\MAIN.C (line 667)
  * Stack frame base $sp, size 24
  * Saved registers at offset -8: ra
  */
void /*$ra*/ MAIN_DoMainInit()
{
}
/*
* Offset 0x8003944C
* C:\kain2\game\PSX\MAIN.C (line 699)
* Stack frame base $sp, size 40
* Saved registers at offset -8: s0 s1 ra
*/
void /*$ra*/ MAIN_ShowPalWarningScreen(struct GameTracker *gameTracker /*$s1*/)
{ // line 1, offset 0x8003944c
	long *warningScreen; // $s0
} // line 10, offset 0x8003949c
  /*
  * Offset 0x800394B0
  * C:\kain2\game\PSX\MAIN.C (line 711)
  * Stack frame base $sp, size 40
  * Saved registers at offset -8: s0 s1 ra
  */
void /*$ra*/ MAIN_ShowLegalWarningScreen(struct GameTracker *gameTracker /*$s1*/)
{ // line 1, offset 0x800394b0
	long *warningScreen; // $s0
} // line 10, offset 0x80039500
  /*
  * Offset 0x80039514
  * C:\kain2\game\PSX\MAIN.C (line 778)
  * Stack frame base $sp, size 32
  * Saved registers at offset -4: s0 s1 s2 ra
  */
void /*$ra*/ MAIN_MainMenuInit()
{ // line 1, offset 0x80039514
	long *addr; // $s2
} // line 1, offset 0x80039514
  /*
  * Offset 0x800396A8
  * C:\kain2\game\PSX\MAIN.C (line 825)
  * Stack frame base $sp, size 32
  * Saved registers at offset -8: s0 s1 ra
  */
void /*$ra*/ MAIN_FreeMainMenuStuff()
{ // line 1, offset 0x800396a8
	long i; // $s1
} // line 11, offset 0x80039710
  /*
  * Offset 0x8003973C
  * C:\kain2\game\PSX\MAIN.C (line 850)
  * Stack frame base $sp, size 120
  * Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 s7 fp ra
  */
long /*$ra*/ MAIN_DoMainMenu(struct GameTracker *gameTracker /*stack 0*/, struct MainTracker *mainTracker /*stack 4*/, long menuPos /*$s3*/)
{ // line 1, offset 0x8003973c
	long *controlCommand; // stack offset -48
	long time; // $a0
	unsigned long **drawot; // $s6
	long i; // $s0
	short menuLineX[3]; // stack offset -64
	short menuLineY[3]; // stack offset -56
} // line 197, offset 0x80039bd0
  /*
  * Offset 0x80039C04
  * C:\kain2\game\PSX\MAIN.C (line 1050)
  * Stack frame base $sp, size 24
  * Saved registers at offset -8: ra
  */
void /*$ra*/ MAIN_ShowFeaturesInit()
{
}
/*
* Offset 0x80039C3C
* C:\kain2\game\PSX\MAIN.C (line 1064)
* Stack frame base $sp, size 64
* Saved registers at offset -4: s0 s1 s2 s3 s4 s5 s6 ra
*/
int /*$ra*/ MainG2(void* appData /*$s6*/)
{ // line 1, offset 0x80039c3c
	struct MainTracker mainTrackerX; // stack offset -48
	struct MainTracker* mainTracker; // $s0
	struct GameTracker* gameTracker; // $s1
	long menuPos; // $s2

	menuPos = 0;
	CheckForDevStation();
	mainOptionsInit = 0;

	if (MainG2_InitEngine(appData, 512, 240, menuPos) != 0)
	{
		MEMPACK_Init();
		LOAD_InitCd();
		LOAD_InitCdLoader("\\BIGFILE.DAT;1", "");

		GAMELOOP_SystemInit(&gameTrackerX);
		gameTrackerX.lastLvl = 255;
		gameTrackerX.currentLvl = 255;
		gameTrackerX.disp = &disp[0];
		InitMainTracker(mainTracker);
		mainTracker->previousState = mainTracker->mainState;

		while (!mainTracker->done)
		{
			switch (mainTracker->mainState - 1)
			{
			case 1:
				MAIN_DoMainInit();
				mainTracker->mainState = 7;
				mainTracker->movieNum = 0;
				//j       def_80039D34
				break;
			case 4:
				DrawSync(0);
				MAIN_ShowPalWarningScreen(gameTracker);
				gameTracker->vblCount = 0;
				mainTracker->mainState = 6;
				//j       def_80039D34     # jumptable 80039D34 default case
				break;
			case 5:
				DrawSync(0);
				MAIN_ShowLegalWarningScreen(gameTracker);
				gameTracker->vblCount = 0;
				mainTracker->mainState = 6;
				//j       def_80039D34     # jumptable 80039D34 default case
				break;
			case 6:
				if (gameTracker->vblCount > 0x1E)
				{
					mainTracker->mainState = 7;
					mainTracker->movieNum = 0;
				}
				//j       def_80039D34
				break;
			case 7:
				DoCinematicStuff(gameTracker, mainTracker);
				if (nosound == 0)
				{
					SOUND_StopAllSound();
				}

				if (DoMainMenu == 0 && gameTrackerX.setDemoMode == 0)
				{
					mainTracker->mainState = 9;
				}
				else
				{
					mainTracker->mainState = 3;
				}
				break;
			case 9:
				gameTrackerX.MorphType = 0;
				ProcessArgs("\kain2\game\psx\kain2.arg", &gameTracker->baseAreaName[0], gameTracker);
				MAIN_MainMenuInit();
				mainTracker->mainState = 10;
				break;
			case 13:
				MAIN_ShowFeaturesInit();
				mainTracker->mainState = 14;
				break;
			case 10:
			case 14:
				menuPos = MAIN_DoMainMenu(gameTracker, mainTracker, menuPos);
				break;
			case 15:
				if (gameTracker->levelDone == 10)
				{
					mainTracker->mainState = 8;
				}
				else
				{
					mainTracker->mainState = 7;
				}
				break;
			case 3:
			case 12:
				ResetPhysobs();

				if (nosound == 0)
				{
					aadInitVolume();
					aadStartMasterVolumeFade(gameTrackerX.sound.gMasterVol, 256, 0);
					gameTrackerX.sound.soundsLoaded = 1;
					aadSetNoUpdateMode(0);
				}//loc_80039EB0

				MAIN_ShowLoadingScreen();
				FONT_ReloadFont();
				DrawSync(0);
				gameTracker.frameCount = 0;
				STREAM_Init();
				GAMELOOP_LevelLoadAndInit(&gameTracker->baseAreaName, gameTracker);

				if (gameTracker->levelDone == 2)
				{
					gameTracker->gameMode = 9;
					gameTracker->gameFlags |= 0x1;
				}//loc_80039F04

				gameTracker->levelDone = 0;
				mainTracker->mainState = 2;

				if (nosound == 0)
				{
					SOUND_FreeDynamicMusic();
					SOUND_LoadDynamicMusic("undrwld1");
				}//loc_80039F28

				while (STREAM_PollLoadQueue() != 0);

				gameTrackerX.vblFrames = 0;
				break;
			case 2:
				aadProcessLoadQueue();
				if ((gameTracker->debugFlags) & 0x80000)
				{
					VOICEXA_Tick();
				}
				//loc_80039F68
				PSX_GameLoop(gameTracker);

				if (gameTracker->levelDone != 0)
				{
					FadeOutSayingLoading(gameTracker);
					SOUND_StopAllSound();
					SOUND_FreeDynamicMusic();
					STREAM_DumpAllLevels(0);
					RemoveAllObjects(gameTracker);
					aadFreeLoadBuffer();
					MEMPACK_FreeByType(4);
					MEMPACK_FreeByType(14);
					MEMPACK_FreeByType(18);
					MEMPACK_FreeByType(22);
					GAMELOOP_ResetGameStates();

					if (gameTracker->levelDone == 2)
					{
						mainTracker->mainState = 7;
						mainTracker->movieNum = 3;
					}
					else if (gameTracker->levelDone != 3 && gameTracker->levelDone != 10)
					{
						mainTracker->mainState = 3;
					}
					else
					{
						mainTracker->mainState = 13;
					}

				}//loc_8003A014

				if (MainG2_UpdateLoop() == 0)
				{
					mainTracker->done = 1;
				}

				break;
			default:
				break;
			}

			STREAM_PollLoadQueue();
		}

		SOUND_StopAllSound();
		SOUND_Free();
		SetDispMask(0);
		DrawSync(0);
		VSync(0);
		DrawSyncCallback(NULL);
		VSyncCallback(NULL);

		EnterCriticalSection();
		StopRCnt(0xF2000000);
		DisableEvent(__timerEvent);
		CloseEvent(__timerEvent);
		ExitCriticalSection();
		VSync(5);
		VSyncCallbacks();
		StopPAD();
		ResetGraph(3);
	}//loc_8003A0CC

	MainG2_ShutDownEngine(appData);
	printf("--->DEMO: Bye!\n");

	return 0;
}