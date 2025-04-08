#include "internals.h"
#include "window.h"



static int m_Fpscount = 0;
static int m_Fps = 0;
static int m_Prevtime = 0;
static int m_Curtime = 0;

Uint64 GetTime(){
    return SDL_GetTicks64();
}


void CalculateFrameRate() {
    static bool init = false;
    static Uint64 lasttime = 0;
    Uint64 currenttime = GetTime();
    if(init == false){
        lasttime = currenttime;
        init = true;
    }
    ++m_Fpscount;
    if (currenttime - lasttime >= 1000) {
        lasttime = currenttime;
        m_Fps = m_Fpscount;
        m_Fpscount = 0;
    }
}


int GetFPS(){
    return m_Fps;
}


void CalculateDeltaTime(){
    m_Prevtime = m_Curtime;
    m_Curtime = GetTime();
}

double GetDeltaTime(){
    return m_Curtime - m_Prevtime;
}

void UpdateWindowTitleWithFPS(char* title){
    char buffer[512];
    sprintf(buffer, "%s - %d FPS", title, GetFPS());
    SetWindowTitle(buffer);
}

static inline uint32_t xorshift32(uint32_t state[static 1])
{
    uint32_t x = state[0];
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state[0] = x;
    return x;
}

uint32_t GenerateRandomValueEx(uint32_t seed) {
    uint32_t state[1];
    state[0] = seed; 
    uint32_t random_number = xorshift32(state);

    return random_number;
}

uint32_t GenerateRandomValueWithinRangeEx(uint32_t seed, uint32_t min, uint32_t max) {
    uint32_t state[1];
    state[0] = seed; 
    uint32_t random_number = xorshift32(state);

    return (random_number % (max - min + 1)) + min;
}


uint32_t GenerateRandomValue() {
    return GenerateRandomValueEx(GetTime());
}

uint32_t GenerateRandomValueWithinRange(uint32_t min, uint32_t max) {
    return GenerateRandomValueWithinRangeEx(GetTime(), min, max);
}


void vec3_distance(vec3 first, vec3 second, vec3 res){
    res[0] = fabsf(first[0] - second[0]);
    res[1] = fabsf(first[1] - second[1]);
    res[2] = fabsf(first[2] - second[2]);
    
}