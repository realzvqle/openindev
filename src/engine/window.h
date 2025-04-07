#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED








#include "../superheader.h"



bool InitWindow(int width, int height, const char* title, Uint32 flags);
bool IsWindowOpen();
void SwapWindow();
bool IsKeyDown(SDL_KeyCode key);
bool IsKeyPressed(SDL_KeyCode key);
void UpdateMousePositionFor3d();
int GetMousePositionFor3dX();
int GetMousePositionFor3dY();
int GetMousePositionX();
int GetMousePositionY();
void LockMouse();
bool IsMouseButtonPressed(Uint8 mouse);
bool DidMouseMove();
void ChangeBackground(vec3 color);
int GetWindowHeight();
int GetWindowWidth();
void SetWindowTitle(char* title);
void SetWindowSize(vec2 size);
void ShutdownWindow();
void CleanupWindow();



#endif