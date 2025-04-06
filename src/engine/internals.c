#include "internals.h"



static int m_Fpscount = 0;
static int m_Fps = 0;

Uint64 GetTime(){
    return SDL_GetTicks64();
}


void CalculateFrameRate() {
    static bool init = false;
    static Uint64 lasttime = 0;
    Uint64 currenttime = GetTime();
    if(init == false){
        lasttime = currenttime;
        init = true;
    }
    ++m_Fpscount;
    if (currenttime - lasttime >= 1000) {
        lasttime = currenttime;
        m_Fps = m_Fpscount;
        m_Fpscount = 0;
    }
}


int GetFPS(){
    return m_Fps;
}