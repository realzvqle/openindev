#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED







#include "openindev.h"

typedef enum _GameMode{
    SURVIVAL,
    CREATIVE
} GameMode;

void SetGameMode(GameMode mode);
GameMode GetGameMode();

#endif