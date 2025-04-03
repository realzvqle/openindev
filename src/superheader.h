#ifndef SUPERHEADER_H_INCLUDED
#define SUPERHEADER_H_INCLUDED




#include "externincludes/SDL2/SDL.h"
#include "externincludes/SDL2/SDL_error.h"
#include "externincludes/SDL2/SDL_events.h"
#include "externincludes/cglm/vec3.h"
#include "externincludes/glad.h"
#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>
#include "externincludes/cglm/cglm.h"
#define fail(message, ...) printf("[-] " message, ##__VA_ARGS__)
#define pass(message, ...) printf("[+] " message, ##__VA_ARGS__)
#define info(message, ...) printf("[!] " message, ##__VA_ARGS__)









#endif