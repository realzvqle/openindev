#include "controls.h"

#include "engine/internals.h"
#include "engine/renderer.h"
#include "engine/window.h"
#include "player.h"
#include "state.h"
#include "terrain.h"

extern Camera g_Cam;


void UpdateControls() {
    
    UpdateMousePositionFor3d();
    static vec2 previousMousePos = {0.0f, 0.0f};  

    float speed = 0.05f * GetDeltaTime();
    float sensitivity = 1;
    vec2 mousePos = {
        (2.0f * GetMousePositionFor3dX()) / GetWindowWidth() - 1.0f,
        1.0f - (2.0f * GetMousePositionFor3dY()) / GetWindowHeight()
    };

    mousePos[0] *= sensitivity;
    mousePos[1] *= sensitivity;
    vec2 mouse_delta = {mousePos[0] - previousMousePos[0], mousePos[1] - previousMousePos[1]};

    previousMousePos[0] = mousePos[0];
    previousMousePos[1] = mousePos[1];

    vec3 forward;;
    vec3 right;
    vec3 up = {0.0f, 1.0f, 0.0f};

    glm_vec3_add(up, g_Cam.up, up);

    glm_vec3_sub(g_Cam.target, g_Cam.pos, forward);
    glm_vec3_normalize(forward);

    glm_vec3_cross(forward, up, right);
    glm_vec3_normalize(right);

    glm_vec3_cross(right, forward, up);
    glm_vec3_normalize(up);

    vec3 rotationAdjusted;
    vec3 res;

    glm_vec3_scale(right, mouse_delta[0], rotationAdjusted);  
    glm_vec3_scale(up, mouse_delta[1], up);  

    glm_vec3_add(rotationAdjusted, up, rotationAdjusted);
    glm_vec3_add(rotationAdjusted, forward, res);

    glm_vec3_add(g_Cam.pos, res, g_Cam.target); 
    float leg;
    float head;
    RenderPlayer((vec3){g_Cam.pos[0], g_Cam.pos[1] - 0.4, g_Cam.pos[2] - 0.3}, g_Cam.target, &leg, &head);
    
    if(GetGameMode() == SURVIVAL){
        if(CheckIfCollidedWithBlock((vec3){g_Cam.pos[0], leg, g_Cam.pos[2]}) == false){
            g_Cam.pos[1] -= 0.01 * GetDeltaTime();
        } 
    }    
    
    
    if (IsKeyDown(SDLK_a)) {
        vec3 scale;
        glm_vec3_scale(right, speed, scale);
        glm_vec3_sub(g_Cam.pos, scale, g_Cam.pos);
        glm_vec3_sub(g_Cam.target, scale, g_Cam.target);
    }
    if (IsKeyDown(SDLK_d)) {
        vec3 scale;
        glm_vec3_scale(right, speed, scale);
        glm_vec3_add(g_Cam.pos, scale, g_Cam.pos);
        glm_vec3_add(g_Cam.target, scale, g_Cam.target);
    }
    if (IsKeyDown(SDLK_s)) {
        vec3 scale;
        glm_vec3_scale(forward, speed, scale);
        float befpos = g_Cam.pos[1];
        float beftar = g_Cam.target[1];
        glm_vec3_sub(g_Cam.pos, scale, g_Cam.pos);
        glm_vec3_sub(g_Cam.target, scale, g_Cam.target);
        if(GetGameMode() == SURVIVAL){
            g_Cam.pos[1] = befpos;
            g_Cam.target[1] = beftar;
        }
    }
    if (IsKeyDown(SDLK_w)) {
        vec3 scale;
        glm_vec3_scale(forward, speed, scale);
        float befpos = g_Cam.pos[1];
        float beftar = g_Cam.target[1];
        glm_vec3_add(g_Cam.pos, scale, g_Cam.pos);  
        glm_vec3_add(g_Cam.target, scale, g_Cam.target);
        if(GetGameMode() == SURVIVAL){
            g_Cam.pos[1] = befpos;
            g_Cam.target[1] = beftar;
        }
    }
    if(IsMouseButtonPressed(SDL_BUTTON_LEFT)){
        vec3 sub;
        vec3 res;
        glm_vec3_sub(g_Cam.target, g_Cam.pos, sub);
        glm_vec3_normalize(sub);
        glm_ray_at(g_Cam.target, sub, 0.5, res);

        CreateBlock(res);
    }
    if(IsKeyPressed(SDLK_p)) SetGameMode(CREATIVE);
    else if(IsKeyPressed(SDLK_l)) SetGameMode(SURVIVAL);
    if(IsKeyPressed(SDLK_ESCAPE)) ShutdownWindow();
    if(IsKeyPressed(SDLK_o)) DeleteRandomBlock();
}
