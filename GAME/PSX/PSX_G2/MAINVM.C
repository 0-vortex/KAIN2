#include "MAIN.H"

#include "G2TYPES.H"

static struct _G2AppDataVM_Type _appDataVM;

int main()
{
	//ClearBss();
	MainG2(&_appDataVM);
	return 0;//@check
}

enum _G2Bool_Enum MainG2_UpdateLoop()
{
	return (enum _G2Bool_Enum)1;
}
