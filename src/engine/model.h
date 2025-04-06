#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED





#include "../superheader.h"



typedef struct _Model {
    int vamount;
    vec3* vertices;
    int iamount;
    int* indices;
    bool pass;
} Model;


Model LoadModel(char* filepath);
void RenderModel(Model* mod, float size, vec3 pos);
void UnloadModel(Model* mod);


#endif