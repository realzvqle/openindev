#include "internals.h"



static int fpscount = 0;
static int fps = 0;

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
    ++fpscount;
    if (currenttime - lasttime >= 1000) {
        lasttime = currenttime;
        fps = fpscount;
        fpscount = 0;
    }
}


int GetFPS(){
    return fps;
}