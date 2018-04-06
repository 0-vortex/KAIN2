#ifndef PLAYER_H
#define PLAYER_H

extern void PLAYER_TurnHead(struct _Instance* instance, short* rotx, short* rotz, struct GameTracker* gameTracker);
extern long PLAYER_OkToLookAround(struct _Instance* instance);
extern void PLAYER_SetLookAround(struct _Instance* instance);
extern void PLAYER_ReSetLookAround(struct _Instance* instance);
extern long PLAYER_HandleLaunchSignal(struct _Instance* instance, struct Signal* signal);
extern int PLAYER_ChangeCostume(struct _Instance* instance, struct GameTracker* gameTracker, char* newModelName);

#endif