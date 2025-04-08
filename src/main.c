#include "controls.h"
#include "engine/internals.h"
#include "engine/model.h"
#include "engine/renderer.h"
#include "engine/text.h"
#include "engine/textures.h"
#include "engine/window.h"

#include "openindev.h"
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
    GenerateTerrain();
    SetupBlockingSystem();
    SetGameMode(SURVIVAL);
    
    while(IsWindowOpen()){
        UpdateWindowTitleWithFPS("Open Indev");
        float topCoords[] = {0.0, 0.0, 0.06, 0.06};     // Top portion of atlas
        float bottomCoords[] = {0.0621, 0.0, 0.11, 0.06};  // Bottom portion of atlas
        //float sideCoords[] = {0.0, 0.5, 1.0, 1.0};    // Side portion of atlas

        DrawGameText(-0.5, -0.5, "zvqle is cool", 0.1);
        RenderBlocks(); 
        
        UpdateControls();
        SwapWindow();
    }
    CleanupBlockingSystem();
    CleanupWindow();
    info("Closed!\n");
    return 0;
}


