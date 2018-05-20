#include "GAMELOOP.H"

#include "MEMPACK.H"
#include "G2TYPES.H"

void GAMELOOP_AllocStaticMemory()
{
	instanceList = (struct _InstanceList*) MEMPACK_Malloc(sizeof(struct _InstanceList), 6);
	instancePool = (struct _InstancePool*) MEMPACK_Malloc(0x9D8C, 6);
	primBase = MEMPACK_Malloc(0x34E18, 6);
	ot[0] = (unsigned long**)primBase;
	ot[1] = (unsigned long**)primBase[0x3000];
	primPool[0] = (struct _PrimPool*)primBase[0x6000];
	primPool[1] = (struct _PrimPool*)primBase[0x1D70C];
	gLightInfo = (struct LightInfo*) MEMPACK_Malloc(sizeof(struct LightInfo), 6);
	vertexPool = (struct _VertexPool*)MEMPACK_Malloc(sizeof(struct _VertexPool), 6);
	polytopeList = (struct _PolytopeList*)MEMPACK_Malloc(sizeof(struct _PolytopeList), 6);
	fxTracker = (struct _FXTracker*)MEMPACK_Malloc(0x81A8, 6);
	gFXT = fxTracker;
	planningPool = (void*)MEMPACK_Malloc(0xBB8, 6);
	enemyPlanPool = (void*)MEMPACK_Malloc(0x3E8, 6);
	GlobalObjects = (struct _ObjectTracker*)MEMPACK_Malloc(0x5A0, 6);
	G2Anim_Install();
}

void GAMELOOP_SystemInit(struct GameTracker* gameTracker)
{
	GAMELOOP_AllocStaticMemory();
	INSTANCE_InitInstanceList(instanceList, instancePool);
	GAMELOOP_InitGameTracker();
}