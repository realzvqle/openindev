#include "terrain.h"
#include "engine/internals.h"
#include "engine/renderer.h"
#include "engine/textures.h"
#include <stdbool.h>


typedef enum _BlockType {
    GRASS,
    STONE,
    BEDROCK,
    COBBLESTONE
} BlockType;

typedef struct _Block {
    vec3 position;
    vec3 color; 
    bool isActive;
    BlockType tex;
} Block;

static Block m_Blocks[512];
static int m_BlockAmount = 0;
static int m_NextBlock;

extern Camera g_Cam;


static Texture m_BlockTex[110];



static unsigned int m_AmountOfBlockTypes = 4;

static inline void LoadAllTextures(){
    for(int i = 0; i < m_AmountOfBlockTypes; i++){
        switch(i){
            case GRASS:
                m_BlockTex[i] = LoadTexture("resources/terrain/grass.png");
                if(m_BlockTex[i].pass == false) fail("Failed Loading Texture for %d!\n", i);
                break;
            case STONE:
                m_BlockTex[i] = LoadTexture("resources/terrain/stone.png");
                if(m_BlockTex[i].pass == false) fail("Failed Loading Texture for %d!\n", i);
                break;
            case BEDROCK:
                m_BlockTex[i] = LoadTexture("resources/terrain/bedrock.png");
                if(m_BlockTex[i].pass == false) fail("Failed Loading Texture for %d!\n", i);
                break;
            case COBBLESTONE:
                m_BlockTex[i] = LoadTexture("resources/terrain/cobblestone.png");
                if(m_BlockTex[i].pass == false) fail("Failed Loading Texture for %d!\n", i);
                break;
        }
    }
}

static inline void UnloadAllTextures(){
    for(int i = 0; i < m_AmountOfBlockTypes; i++){
        FreeTexture(m_BlockTex[i]);
    }
}

static inline int UpdateFreeBlockList(){
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
static inline void StartCheckFreeBlockThread(){
    SDL_CreateThread(UpdateFreeBlockList, "UpdateFreeBlockList", FALSE);
}

void SetupBlockingSystem(){
    StartCheckFreeBlockThread();
    LoadAllTextures();
}

void CleanupBlockingSystem(){
    UnloadAllTextures();
}

void CreateFirstBlocks(vec3 pos){
    pos[0] = roundf(pos[0]/ 0.5) * 0.5;
    pos[1] = roundf(pos[1]/ 0.5) * 0.5;
    pos[2] = roundf(pos[2]/ 0.5) * 0.5;
    glm_vec3_copy(pos, m_Blocks[m_BlockAmount].position);
    m_Blocks[m_BlockAmount].position[2]+=1;
    m_Blocks[m_BlockAmount].isActive = true;
    m_Blocks[m_BlockAmount].tex = GRASS;
    m_BlockAmount++;
}

void RenderBlocks(){
    for(int i = 0; i < m_BlockAmount; i++){
        if(m_Blocks[i].isActive == false) continue;
        RenderCubeTex(0.5, m_Blocks[i].position, (vec3){0, 0, 0}, m_BlockTex[m_Blocks[i].tex], 0.0f, 1.0f, false);        
    } 
}

bool CheckIfCollidedWithBlock(vec3 pos){
    for(int i = 0; i < m_BlockAmount; i++){
        vec3 res;
        vec3_distance(pos, m_Blocks[i].position, res);
        if(res[0] <= 0.5 && res[1] <= 0.5 && res[2] <= 0.5){
            info("Colliding!\n");
            return true;
        } 
    } 
    return false;
}


void CreateBlock(vec3 pos){
    pos[0] = roundf(pos[0]/ 0.5) * 0.5;
    pos[1] = roundf(pos[1]/ 0.5) * 0.5;
    pos[2] = roundf(pos[2]/ 0.5) * 0.5;
    glm_vec3_copy(pos, m_Blocks[m_NextBlock].position);
    m_Blocks[m_NextBlock].position[2]+=1;
    m_Blocks[m_BlockAmount].tex = COBBLESTONE;
    m_Blocks[m_NextBlock].isActive = true;
}

void DeleteRandomBlock(){
    int num = GenerateRandomValueWithinRange(0, m_BlockAmount);
    m_Blocks[num].isActive = false;
}

void GenerateTerrain(){
    for(int i = 0; i > -20; i--){
        for(int j = 0; j < 10; j++){
            vec3 pos = {j * 0.5, -3, i * 0.5};
            CreateFirstBlocks(pos);
        }
    }
}