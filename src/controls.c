#include "controls.h"

#include "engine/renderer.h"
#include "engine/window.h"

void UpdateControls(){
    if(IsKeyDown(SDLK_w)){
        ChangeCameraPositionY(0.01);
    }
    if(IsKeyDown(SDLK_s)){
        ChangeCameraPositionY(-0.01);
    }
    if(IsKeyDown(SDLK_a)){
        ChangeCameraPositionX(0.01);   
    }
    if(IsKeyDown(SDLK_d)){
        ChangeCameraPositionX(-0.01);
    }
    if(IsKeyDown(SDLK_p)){
        ChangeCameraPositionZ(-0.01);
    }
    if(IsKeyDown(SDLK_l)){
        ChangeCameraPositionZ(0.01);
    }
}