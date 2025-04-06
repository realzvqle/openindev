#include "model.h"



/*

    Open-Indev Model Loading System

    NOT READY FOR USE, DO NOT USE THIS IN THE BASE GAME - zvqle


*/




Model LoadModel(char* filepath){
    Model mod = {0, false};
    info("Opening %s..\n", filepath);
    FILE* fp = fopen(filepath, "r");
    if(!fp){
        fail("Couldn't find file!\n");
        return mod;
    }
    char buffer[512];
    mod.vertices = calloc(1, sizeof(vec3));
    mod.indices = calloc(1, sizeof(int));
    while(fgets(buffer, 512, fp)){
        if(buffer[0] == 'v' && buffer[1] == ' '){
            float v1f, v2f, v3f;
            sscanf(buffer, "v %f %f %f", &v1f, &v2f, &v3f);
            mod.vamount++;
            int prev = mod.vamount - 1;
            mod.vertices = realloc(mod.vertices, mod.vamount * sizeof(vec3));
            //info("Reallocating Memory for Vertices with Size of %llu\n", mod.vamount * sizeof(vec3));
            mod.vertices[prev][0] = v1f;
            mod.vertices[prev][1] = v2f;
            mod.vertices[prev][2] = v3f;
            //info("[?] - first - %f second - %f third - %f\n", mod.vertices[prev][0], mod.vertices[prev][1], mod.vertices[prev][2]);
        } 
        else if(buffer[0] == 'f' && buffer[1] == ' '){
            int v1f, v2f, v3f, v4f, v5f, v6f, v7f, v8f, v9f;
            sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1f, &v2f, &v3f,
                  &v4f, &v5f, &v6f, &v7f, &v8f, &v9f);
            mod.iamount+=9;
            mod.indices = realloc(mod.indices, mod.iamount * sizeof(int));
            //info("Reallocating Memory for Indices with Size of %llu\n", mod.iamount * sizeof(int));
            mod.indices[mod.iamount-9] = v1f - 1;
            mod.indices[mod.iamount-8] = v2f - 1;
            mod.indices[mod.iamount-7] = v3f - 1;
            mod.indices[mod.iamount-6] = v4f - 1;
            mod.indices[mod.iamount-5] = v5f - 1;
            mod.indices[mod.iamount-4] = v6f - 1;
            mod.indices[mod.iamount-3] = v7f - 1;
            mod.indices[mod.iamount-2] = v8f - 1;
            mod.indices[mod.iamount-1] = v9f - 1;
            // info("f %d/%d/%d %d/%d/%d %d/%d/%d", v1f, v2f, v3f,
            //       v4f, v5f, v6f, v7f, v8f, v9f);
        }
        
    }
    mod.pass = true;
    fclose(fp);
    return mod;
}

void RenderModel(Model* mod, float size, vec3 pos){
    float half = size / 2.0f;

    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 1.0, 1.0);  
    for(int i = 0; i < mod->vamount; i++){
        glVertex3f(
            (pos[0] - half) + mod->vertices[i][0], 
            (pos[1] - half) + mod->vertices[i][1], 
            (pos[2]) + mod->vertices[i][2]
        );
    }
    glEnd();
}

void UnloadModel(Model* mod){
    free(mod->vertices);
    free(mod->indices);
    mod->vamount = 0;
    mod->iamount = 0;
    mod->pass = false;
}

