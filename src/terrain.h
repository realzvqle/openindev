#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED







#include "superheader.h"






void RenderBlocks();
void CreateBlock(vec3 pos);
void GenerateTerrain();
void StartCheckFreeBlockThread();
void DeleteRandomBlock();




#endif