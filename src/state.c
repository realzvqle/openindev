#include "state.h"


static GameMode m_GameMode = SURVIVAL;



void SetGameMode(GameMode mode){
    m_GameMode = mode;
}

GameMode GetGameMode(){
    return m_GameMode;
}