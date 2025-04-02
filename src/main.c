#include "externincludes/SDL2/SDL.h"
#include "externincludes/SDL2/SDL_error.h"
#include "externincludes/cglm/vec3.h"
#include "externincludes/glad.h"
#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>
#include "externincludes/cglm/cglm.h"
#define fail(message, ...) printf("[-] " message, ##__VA_ARGS__)
#define pass(message, ...) printf("[+] " message, ##__VA_ARGS__)
#define info(message, ...) printf("[!] " message, ##__VA_ARGS__)


void render(float size) {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    
    float half = size / 2;

    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex2f(-half, -half);
    
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex2f(half, -half);
    
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex2f(0.0f, half);
    
    glEnd();
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fail("Couldn't initialize SDL! %s\n", SDL_GetError());
        return -1;
    }
    float h = 0;
    float y = 0;
    glm_vec3_dup(&h, &y);

    SDL_Window* window = SDL_CreateWindow("Open Indev!",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1600, 900,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        fail("Couldn't Create SDL Window! %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fail("Couldn't Create OpenGL Context! %s\n", SDL_GetError());

        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fail("Couldn't Start GLAD!\n");
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        render(2);
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
