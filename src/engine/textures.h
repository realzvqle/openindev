#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED









#include "engine.h"


typedef struct _Texture {
    unsigned char* image;
    int w;
    int h;
    int comp;
    unsigned int id;
    bool pass;
} Texture;


Texture LoadTexture(char* path);
void FreeTexture(Texture tex);


#endif