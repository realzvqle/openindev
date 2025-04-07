#include "renderer.h"
#include "text.h"
#include "window.h"




/*

    Open-Indev Renderer  

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



void SetupCamera() {
    glm_vec3_copy((vec3){0.0f, 0.0f, -5.0f}, g_Cam.pos);
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