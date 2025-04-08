#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED







#include "openindev.h"





void SetupBlockingSystem();
void CleanupBlockingSystem();
void RenderBlocks();
void CreateBlock(vec3 pos);
void GenerateTerrain();
void DeleteRandomBlock();
bool CheckIfCollidedWithBlock(vec3 pos);



#endif