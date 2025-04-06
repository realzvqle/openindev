#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED







#include "../superheader.h"


void RenderSquares(float size, vec3 pos, vec3 color);
void RenderSquares_2(float size, vec3 pos);
void RenderCube(float size, vec3 pos, vec3 rot, bool isLines);
typedef struct _Camera {
    vec3 pos;
    vec3 up;
    vec3 target;
    float fovy;
} Camera;


void SetupCamera();
void ChangeCameraPositionX(float amount);
void ChangeCameraPositionY(float amount);
void ChangeCameraPositionZ(float amount);
void ApplyCameraTransform();
void UpdateCamera();
float* GetCameraPositionAll();
float* GetCameraTargetAll();
float* GetCameraUpAll();
float GetCameraFOV();
#endif