#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED








#include "../superheader.h"



bool InitWindow(int width, int height, const char* title, Uint32 flags);
bool IsWindowOpen();
void SwapWindow();
bool IsKeyDown(SDL_KeyCode key);
bool IsKeyPressed(SDL_KeyCode key);
void SetWindowTitle(char* title);
int GetWindowHeight();
int GetWindowWidth();
void ShutdownWindow();
void CleanupWindow();



#endif