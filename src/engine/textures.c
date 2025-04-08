#define STB_IMAGE_IMPLEMENTATION
#include "external/stb/stb_image.h"

#include "textures.h"





Texture LoadTexture(char* path){
    Texture tex = {NULL, 0, 0, 0, 0, false};
    int w, h, comp;
    unsigned char* image = stbi_load(path, &w, &h, &comp, STBI_rgb_alpha);
    if (image == NULL) {
        return tex;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    tex = (Texture){NULL, w, h, comp, textureID, true};
    return tex;
}



void FreeTexture(Texture tex){
    glDeleteTextures(1, &tex.id);
    tex.w = 0;
    tex.h = 0;
    tex.pass = false;
}