#include "window.h"
#include "internals.h"



static bool running = true;
static SDL_Event event;
static SDL_GLContext glContext;
static SDL_Window* window;

static SDL_KeyCode keydown;
static SDL_KeyCode keypressed;

bool InitWindow(int width, int height, const char* title, Uint32 flags){
    #ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX);
    #endif
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fail("Couldn't initialize SDL! %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow(title,
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             width, height,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | flags);
    if (!window) {
        fail("Couldn't Create SDL Window! %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fail("Couldn't Create OpenGL Context! %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fail("Couldn't Start GLAD!\n");
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    return true;
}

bool IsKeyPressed(SDL_KeyCode key){
    if(keypressed == key){
        return true;
    }
    return false;
}

bool IsKeyDown(SDL_KeyCode key){
    if(keydown == key){
        keydown = 0;
        return true;
    }
    return false;
}

int GetWindowWidth(){
    int h;
    int w;
    SDL_GetWindowSize(window, &w, &h);
    return w;
}

void SetWindowTitle(char* title){
    SDL_SetWindowTitle(window, title);
}

int GetWindowHeight(){
    int h;
    int w;
    SDL_GetWindowSize(window, &w, &h);
    return h;
}

bool IsWindowOpen(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if(event.type == SDL_WINDOWEVENT){
            if(event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
            }
        }
        if(event.type == SDL_KEYDOWN){
            keypressed = event.key.keysym.sym; 
            
        } else {
            if(keydown == event.key.keysym.sym){
                keypressed = 0;
            }
        }
        if(event.type == SDL_KEYDOWN){
            keydown = event.key.keysym.sym;   
        } 
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    CalculateFrameRate();
    return running;
}

void ShutdownWindow(){
    running = false;
}

void SwapWindow(){
    SDL_GL_SwapWindow(window);
}

void CleanupWindow(){
    
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

