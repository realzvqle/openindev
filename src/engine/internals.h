#ifndef INTERNALS_H_INCLUDED
#define INTERNALS_H_INCLUDED







#include "../superheader.h"



void CalculateFrameRate();
Uint64 GetTime();
int GetFPS();
void CalculateDeltaTime();
double GetDeltaTime();
void UpdateWindowTitleWithFPS(char* title);
uint32_t GenerateRandomValueEx(uint32_t seed);
uint32_t GenerateRandomValueWithinRangeEx(uint32_t seed, uint32_t min, uint32_t max);
uint32_t GenerateRandomValue();
uint32_t GenerateRandomValueWithinRange(uint32_t min, uint32_t max);
#endif