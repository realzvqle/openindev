#include "model.h"







Model LoadModel(char* filepath){
    Model mod = {0, false};
    info("Opening %s..\n", filepath);
    FILE* fp = fopen(filepath, "r");
    if(!fp){
        fail("Couldn't find file!\n");
        return mod;
    }
    char buffer[512];
    mod.vertices = calloc(mod.amount, sizeof(vec3));

    while(fgets(buffer, 512, fp)){
        if(buffer[0] != 'v') continue;
        float v1f, v2f, v3f;
        sscanf(buffer, "v %f %f %f", &v1f, &v2f, &v3f);
        // strtok(buffer, " ");
        // // char* vertices = strtok(NULL, "\n");
        // // char* v1 = strtok(vertices, " ");
        // // char* v2 = strtok(NULL, " ");
        // // char* v3 = strtok(NULL, "\n");
        // // if(v3 == NULL) continue;
        // // float v1f = atof(v1);
        // // float v2f = atof(v2);
        // // float v3f = atof(v3);
        mod.amount++;
        int prev = mod.amount - 1;
        mod.vertices = realloc(mod.vertices, mod.amount * sizeof(vec3));
        info("Allocating Memory with Size of %llu\n", mod.amount * sizeof(vec3));
        mod.vertices[prev][0] = v1f;
        mod.vertices[prev][1] = v2f;
        mod.vertices[prev][2] = v3f;
        info("[?] - first - %f second - %f third - %f\n", mod.vertices[prev][0], mod.vertices[prev][1], mod.vertices[prev][2]);
    }
    mod.pass = true;
    return mod;
}

void RenderModel(Model* mod, float size, vec3 pos){
    float half = size / 2.0f;

    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 1.0, 0.0);  
    for(int i = 0; i < mod->amount; i++){
        glVertex3f(
            (pos[0] - half) + mod->vertices[i][0], 
            (pos[1] - half) + mod->vertices[i][1], 
            (pos[2]) + mod->vertices[i][2]
        );
    }
    glEnd();
}

