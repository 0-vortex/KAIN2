#ifndef VIEWVM_H
#define VIEWVM_H

#include "G2TYPES.H"

extern enum _G2Bool_Enum ViewportG2_Init(void *appData, unsigned int screenWidth, unsigned int screenHeight);
extern void ViewportG2_ShutDown(void* appData);

#endif