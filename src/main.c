#include "controls.h"
#include "engine/internals.h"
#include "engine/model.h"
#include "engine/renderer.h"
#include "engine/text.h"
#include "engine/window.h"
#include "externincludes/SDL2/SDL_keycode.h"
#include "externincludes/SDL2/SDL_mouse.h"
#include "externincludes/SDL2/SDL_video.h"
#include "externincludes/cglm/ray.h"
#include "superheader.h"
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
    StartCheckFreeBlockThread();
    while(IsWindowOpen()){
        UpdateWindowTitleWithFPS("Open Indev");
        DrawGameText(-0.5, -0.5, "zvqle is cool", 0.1);
        RenderBlocks(); 
        if(IsMouseButtonPressed(SDL_BUTTON_LEFT)){
            vec3 sub;
            vec3 res;
            glm_vec3_sub(g_Cam.target, g_Cam.pos, sub);
            glm_vec3_normalize(sub);
            glm_ray_at(g_Cam.target, sub, 0.5, res);

            CreateBlock(res);
        }
        if(IsKeyPressed(SDLK_ESCAPE)) ShutdownWindow();
        if(IsKeyPressed(SDLK_o)) DeleteRandomBlock();
        UpdateControls();
        SwapWindow();
    }
    CleanupWindow();
    info("Closed!\n");
    return 0;
}


