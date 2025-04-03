#include "controls.h"
#include "engine/internals.h"
#include "engine/render.h"
#include "engine/text.h"
#include "engine/window.h"
#include "externincludes/SDL2/SDL_keycode.h"
#include "externincludes/SDL2/SDL_video.h"
#include "superheader.h"
#include <winuser.h>

typedef struct _Cube {
    vec3 position;
    vec3 color; // not used now
} Cube;

Cube cubes[512];
static int amount = 0;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    bool result = InitWindow(1600, 900, "Open Indev", 0);
    SetupCamera();
    if(result == false) return -1;
    

    glm_vec3_copy((vec3){0.0, 0.0, -5.0}, cubes[amount].position);
    cubes[amount].position[2]+=1;
    amount++;

    while(IsWindowOpen()){
        UpdateCamera();
        char buffer[512];
        sprintf(buffer, "Open Indev - %d FPS", GetFPS());
        SetWindowTitle(buffer);
        for(int i = 0; i < amount; i++){
            RenderCube(0.5, cubes[i].position, (vec3){0, 0, 0}, false);        
        } 
        if(IsKeyPressed(SDLK_m)){
            glm_vec3_copy(GetCameraPositionAll(), cubes[amount].position);
            cubes[amount].position[2]+=1;
            amount++;
        }
        UpdateControls();
        SwapWindow();
    }
    CleanupWindow();
    return 0;
}


