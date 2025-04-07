#include "terrain.h"
#include "engine/internals.h"
#include "engine/renderer.h"
#include <stdbool.h>


typedef struct _Block {
    vec3 position;
    vec3 color; 
    bool isActive;
} Block;

static Block m_Blocks[512];
static int m_BlockAmount = 0;
static int m_NextBlock;

int UpdateFreeBlockList(){
    bool increment;
    while(1){
        for(int i = 0; i < m_BlockAmount; i++){
            if(m_Blocks[i].isActive == false){
                m_NextBlock = i;
                increment = false;
                break;
            } else increment = true;
        }
        if(increment == true){
            m_Blocks[m_BlockAmount++].isActive = false;
            m_NextBlock = m_BlockAmount;
            increment = false;
        }
        SDL_Delay(100);
        //info("%d is the next index to be used\n", m_NextBlock);
        //SDL_Delay(3000);
    }
    return 0;
}
void StartCheckFreeBlockThread(){
    SDL_CreateThread(UpdateFreeBlockList, "UpdateFreeBlockList", FALSE);
}

void CreateFirstBlocks(vec3 pos){
    pos[0] = roundf(pos[0]/ 0.5) * 0.5;
    pos[1] = roundf(pos[1]/ 0.5) * 0.5;
    pos[2] = roundf(pos[2]/ 0.5) * 0.5;
    glm_vec3_copy(pos, m_Blocks[m_BlockAmount].position);
    m_Blocks[m_BlockAmount].position[2]+=1;
    m_Blocks[m_BlockAmount].isActive = true;

    m_BlockAmount++;
}

void RenderBlocks(){
    for(int i = 0; i < m_BlockAmount; i++){
        if(m_Blocks[i].isActive == false) continue;
        RenderCube(0.5, m_Blocks[i].position, (vec3){0, 0, 0}, false);        
    } 
}



void CreateBlock(vec3 pos){
    pos[0] = roundf(pos[0]/ 0.5) * 0.5;
    pos[1] = roundf(pos[1]/ 0.5) * 0.5;
    pos[2] = roundf(pos[2]/ 0.5) * 0.5;
    glm_vec3_copy(pos, m_Blocks[m_NextBlock].position);
    m_Blocks[m_NextBlock].position[2]+=1;
    m_Blocks[m_NextBlock].isActive = true;
}

void DeleteRandomBlock(){
    int num = GenerateRandomValueWithinRange(0, m_BlockAmount);
    m_Blocks[num].isActive = false;
}

void GenerateTerrain(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            vec3 pos = {j * 0.5, 0, i * 0.5};
            CreateFirstBlocks(pos);
        }
    }
}