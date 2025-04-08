#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED




/*
     KUPBLE ENGINE
*/


#include "external/SDL2/SDL.h"
#include "external/SDL2/SDL_error.h"
#include "external/SDL2/SDL_events.h"
#include "external/cglm/vec3.h"
#include "external/glad.h"
#include <stdbool.h>
#include <stdio.h>
#include "external/cglm/cglm.h"
#include <string.h>
#define fail(message, ...) printf("[-] " message, ##__VA_ARGS__)
#define pass(message, ...) printf("[+] " message, ##__VA_ARGS__)
#define info(message, ...) printf("[!] " message, ##__VA_ARGS__)

#ifdef _WIN32
#include <Windows.h>
#endif







#endif