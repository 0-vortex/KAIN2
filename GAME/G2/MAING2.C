#include "G2TYPES.H"

#include "VIEWVM.H"
#include "INPUTVM.H"
#include "RENDERRA.H"

enum _G2Bool_Enum MainG2_InitEngine(void* appData, unsigned int screenWidth, unsigned int screenHeight, char* filesystemName)
{
	if (ViewportG2_Init(appData, screenWidth, screenHeight) == 0)
	{
		return (enum _G2Bool_Enum)0;
	}
	
	if (InputG2_Init(appData) == 0)
	{
		return (enum _G2Bool_Enum)0;
	}

	return (_G2Bool_Enum)(0 < RenderG2_Init(appData) ? 1 : 0);
}

void MainG2_ShutDownEngine(void* appData)
{
	RenderG2_ShutDown(appData);
	ViewportG2_ShutDown(appData);
	InputG2_ShutDown(appData);
}