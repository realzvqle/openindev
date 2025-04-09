#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED







#include "engine.h"
#include "textures.h"


void RenderSquares(float size, vec3 pos, vec3 color);
void RenderSquares_2(float size, vec3 pos);
void RenderSquares_e(float size, vec3 pos, Texture tex);
void RenderCube(float size, vec3 pos, vec3 rot, bool isLines);
typedef struct _Camera {
    vec3 pos;
    vec3 up;
    vec3 target;
    float fovy;
} Camera;


void SetupCamera();
void ApplyCameraTransform();
void UpdateCamera();
float* GetCameraPositionAll();
float* GetCameraTargetAll();
float* GetCameraUpAll();
float GetCameraFOV();
void RenderCubeTex(float size, vec3 pos, vec3 rot, Texture tex, float texpos1, float texpos2, bool isLines);
void SetupOrthoProjection();
void DrawUIText(float x, float y, vec3 color, char* text);
#endif