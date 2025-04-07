#include "controls.h"

#include "engine/internals.h"
#include "engine/renderer.h"
#include "engine/window.h"

extern Camera g_Cam;


void UpdateControls() {
    UpdateMousePositionFor3d();
    static vec2 previousMousePos = {0.0f, 0.0f};  

    float speed = 0.1f * GetDeltaTime();
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
SKIPROT:
    
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
        glm_vec3_sub(g_Cam.pos, scale, g_Cam.pos);
        glm_vec3_sub(g_Cam.target, scale, g_Cam.target);
    }
    if (IsKeyDown(SDLK_w)) {
        vec3 scale;
        glm_vec3_scale(forward, speed, scale);
        glm_vec3_add(g_Cam.pos, scale, g_Cam.pos);
        glm_vec3_add(g_Cam.target, scale, g_Cam.target);
    }
}
