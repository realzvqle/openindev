#include "controls.h"
#include "engine/internals.h"
#include "engine/model.h"
#include "engine/renderer.h"
#include "engine/text.h"
#include "engine/textures.h"
#include "engine/window.h"

#include "openindev.h"
#include "player.h"
#include "state.h"
#include "terrain.h"

extern Camera g_Cam;




#ifdef _WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
#ifndef _WIN32
int main(int argc, char* argv[])
#endif
{
    bool result = InitWindow(1600, 900, "Open Indev", SDL_WINDOW_RESIZABLE);
    if(result == false) return -1;
    LockMouse();
    SetupBlockingSystem();
    SetGameMode(CREATIVE);
    vec3 pos = {0.0, 0.0, -5.0};

    while(IsWindowOpen()){
        UpdateWindowTitleWithFPS("Open Indev");
        RenderPlayer((vec3){0.0, 0.0, -5.0}, (vec3){90.0f, 90.0f, 90.0f}, NULL, NULL);
        DrawGameText(-0.5, -0.5, "zvqle is cool", 0.1);        
        UpdateControls();
        RenderBlocks();    
        SwapWindow();
    }
    CleanupBlockingSystem();
    CleanupWindow();
    info("Closed!\n");
    return 0;
}


