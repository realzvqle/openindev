#include "renderer.h"
#include "engine.h"
#include "text.h"
#include "window.h"



/*

    Kupble Renderer  

*/

Camera g_Cam;



void RenderSquares(float size, vec3 pos, vec3 color) {
    float half = size / 2.0f;

    glBegin(GL_TRIANGLES);
    glColor3f(color[0], color[1], color[2]);  
    glVertex3f(pos[0] - half, pos[1] - half, pos[2]); 
    glVertex3f(pos[0] + half, pos[1] - half, pos[2]);  
    glVertex3f(pos[0] - half, pos[1] + half, pos[2]);  

    glVertex3f(pos[0] + half, pos[1] - half, pos[2]);  
    glVertex3f(pos[0] + half, pos[1] + half, pos[2]);  
    glVertex3f(pos[0] - half, pos[1] + half, pos[2]); 

    
    glEnd();
}

void RenderSquares_2(float size, vec3 pos) {
    float half = size / 2.0f;

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);  
    glVertex3f(pos[0] - half, pos[1] - half, pos[2]);

    glColor3f(0.0, 1.0, 0.0);  
    glVertex3f(pos[0] + half, pos[1] + half, pos[2]);

    glColor3f(0.0, 0.0, 1.0);  
    glVertex3f(pos[0] + half, pos[1] - half, pos[2]);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(pos[0] - half, pos[1] - half, pos[2]);

    glColor3f(0.0, 1.0, 0.0);  
    glVertex3f(pos[0] + half, pos[1] + half, pos[2]);

    glColor3f(1.0, 1.0, 1.0);  
    glVertex3f(pos[0] - half, pos[1] + half, pos[2]);
    glEnd();
}

void RenderSquares_e(float size, vec3 pos, Texture tex) {
    float half = size / 2.0f;
    
    glEnable(GL_TEXTURE_2D);  
    glBindTexture(GL_TEXTURE_2D, tex.id);  

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); 
    glVertex3f(pos[0] - half, pos[1] - half, pos[2]); 

    glTexCoord2f(1.0f, 0.0f); 
    glVertex3f(pos[0] + half, pos[1] - half, pos[2]);

    glTexCoord2f(1.0f, 1.0f); 
    glVertex3f(pos[0] + half, pos[1] + half, pos[2]); 

    glTexCoord2f(0.0f, 1.0f); 
    glVertex3f(pos[0] - half, pos[1] + half, pos[2]);


    glEnd();

    glDisable(GL_TEXTURE_2D);  
}



void RenderCube(float size, vec3 pos, vec3 rot, bool isLines) {
    glPushMatrix();  
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
    glRotatef(rot[1], 0.0f, 1.0f, 0.0f); 
    glRotatef(rot[2], 0.0f, 0.0f, 1.0f); 

    float half = size / 2.0f;
    isLines ? glBegin(GL_LINES) : glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(-half, -half,  half);
    glVertex3f( half, -half,  half);
    glVertex3f( half,  half,  half);
    glVertex3f(-half,  half,  half);

    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-half, -half, -half);
    glVertex3f( half, -half, -half);
    glVertex3f( half,  half, -half);
    glVertex3f(-half,  half, -half);

    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(-half,  half, -half);
    glVertex3f( half,  half, -half);
    glVertex3f( half,  half,  half);
    glVertex3f(-half,  half,  half);

    glColor3f(1.0f, 1.0f, 0.0f); 
    glVertex3f(-half, -half, -half);
    glVertex3f( half, -half, -half);
    glVertex3f( half, -half,  half);
    glVertex3f(-half, -half,  half);

    glColor3f(1.0f, 0.0f, 1.0f); 
    glVertex3f( half, -half, -half);
    glVertex3f( half,  half, -half);
    glVertex3f( half,  half,  half);
    glVertex3f( half, -half,  half);

    glColor3f(0.0f, 1.0f, 1.0f); 
    glVertex3f(-half, -half, -half);
    glVertex3f(-half,  half, -half);
    glVertex3f(-half,  half,  half);
    glVertex3f(-half, -half,  half);

    glEnd();
    glPopMatrix();
}

void RenderCubeTex(float size, vec3 pos, vec3 rot, Texture tex, float texpos1, float texpos2, bool isLines) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.id);
    glPushMatrix();  
    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
    glRotatef(rot[1], 0.0f, 1.0f, 0.0f); 
    glRotatef(rot[2], 0.0f, 0.0f, 1.0f); 

    
    float half = size / 2.0f;
    isLines ? glBegin(GL_LINES) : glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(texpos2, texpos2); 
    glVertex3f(-half, -half,  half);
    glTexCoord2f(texpos1, texpos2); 
    glVertex3f( half, -half,  half);
    glTexCoord2f(texpos1, texpos1); 
    glVertex3f( half,  half,  half);
    glTexCoord2f(texpos2, texpos1); 
    glVertex3f(-half,  half,  half);

    glTexCoord2f(texpos2, texpos2); 
    glVertex3f(-half, -half, -half);
    glTexCoord2f(texpos1, texpos2); 
    glVertex3f( half, -half, -half);
    glTexCoord2f(texpos1, texpos1); 
    glVertex3f( half,  half, -half);
    glTexCoord2f(texpos2, texpos1); 
    glVertex3f(-half,  half, -half);

    glTexCoord2f(texpos2, texpos2);
    glVertex3f(-half,  half, -half);
    glTexCoord2f(texpos1, texpos2); 
    glVertex3f( half,  half, -half);
    glTexCoord2f(texpos1, texpos1); 
    glVertex3f( half,  half,  half);
    glTexCoord2f(texpos2, texpos1);
    glVertex3f(-half,  half,  half);

    glTexCoord2f(texpos2, texpos2);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(texpos1, texpos2); 
    glVertex3f( half, -half, -half);
    glTexCoord2f(texpos1, texpos1); 
    glVertex3f( half, -half,  half);
    glTexCoord2f(texpos2, texpos1);
    glVertex3f(-half, -half,  half);

    glTexCoord2f(texpos2, texpos2);
    glVertex3f( half, -half, -half);
    glTexCoord2f(texpos1, texpos2); 
    glVertex3f( half,  half, -half);
    glTexCoord2f(texpos1, texpos1); 
    glVertex3f( half,  half,  half);
    glTexCoord2f(texpos2, texpos1);
    glVertex3f( half, -half,  half);

    glTexCoord2f(texpos2, texpos2);
    glVertex3f(-half, -half, -half);
    glTexCoord2f(texpos1, texpos2); 
    glVertex3f(-half,  half, -half);
    glTexCoord2f(texpos1, texpos1); 
    glVertex3f(-half,  half,  half);
    glTexCoord2f(texpos2, texpos1);
    glVertex3f(-half, -half,  half);

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void SetupCamera() {
    glm_vec3_copy((vec3){1.0f, 1.0f, -5.0f}, g_Cam.pos);
    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, g_Cam.target);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, g_Cam.up);
    g_Cam.fovy = glm_rad(90.0f);

    mat4 perspective_matrix;
    glm_perspective(g_Cam.fovy, (float)GetWindowWidth()/GetWindowHeight(), 0.1f, 1000.0f, perspective_matrix);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((const float*)perspective_matrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  

    UpdateCamera();
}

void DrawUIText(float x, float y, vec3 color, char* text) {
    RenderSquares_2(0.2, (vec3){0.5, 0.5, 5.0});

}

void UpdateCamera() {
    mat4 view_matrix;
    glm_lookat(g_Cam.pos, g_Cam.target, g_Cam.up, view_matrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf((const float*)view_matrix);
}


float* GetCameraPositionAll(){
    return g_Cam.pos;
}

float* GetCameraTargetAll(){
    return g_Cam.target;
}

float* GetCameraUpAll(){
    return g_Cam.up;
}

float GetCameraFOV(){
    return g_Cam.fovy;
}