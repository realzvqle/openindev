#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED





#include "../superheader.h"



typedef struct _Model {
    int amount;
    bool pass;
    vec3* vertices;
} Model;


Model LoadModel(char* filepath);
void RenderModel(Model* mod, float size, vec3 pos);



#endif