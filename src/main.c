#include "controls.h"
#include "engine/internals.h"
#include "engine/model.h"
#include "engine/renderer.h"
#include "engine/text.h"
#include "engine/window.h"
#include "externincludes/SDL2/SDL_keycode.h"
#include "externincludes/SDL2/SDL_video.h"
#include "superheader.h"

typedef struct _Cube {
    vec3 position;
    vec3 color; // not used now
} Cube;

Cube cubes[512];
static int amount = 0;

#ifdef _WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
#ifndef _WIN32
int main(int argc, char* argv[])
#endif
{
    bool result = InitWindow(1600, 900, "Open Indev", SDL_WINDOW_RESIZABLE);
    SetupCamera();
    if(result == false) return -1;
    

    // glm_vec3_copy((vec3){0.0, 0.0, -5.0}, cubes[amount].position);
    // cubes[amount].position[2]+=1;
    // amount++;
    Model mod = LoadModel("resources/miku.obj");
    while(IsWindowOpen()){
        UpdateCamera();
        char buffer[512];
        sprintf(buffer, "Open Indev - %d FPS", GetFPS());
        SetWindowTitle(buffer);
        RenderModel(&mod, 0.001, (vec3){-0.5, -0.5, 5.0});
        //DrawGameText(-0.5, -0.5, "Hello", 0.2);
        for(int i = 0; i < amount; i++){
            RenderCube(0.5, cubes[i].position, (vec3){0, 0, 0}, false);        
        } 
        if(IsKeyPressed(SDLK_m)){
            glm_vec3_copy(GetCameraPositionAll(), cubes[amount].position);
            cubes[amount].position[2]+=1;
            amount++;
        }
        if(IsKeyPressed(SDLK_n)){
            ChangeBackground((vec4){0.0, 0.5, 0.5, 1.0});
        }
        if(IsKeyPressed(SDLK_b)){
            SetWindowSize((vec2){800, 600});
            ChangeBackground((vec4){0.0, 0.2, 0.2, 1.0});
        }
        UpdateControls();
        SwapWindow();
    }
    CleanupWindow();
    UnloadModel(&mod);
    info("Closed!\n");
    return 0;
}


