#include "window.h"
#include "internals.h"
#include "renderer.h"



static bool m_Running = true;
static SDL_Event m_Event;
static SDL_GLContext m_GlContext;
static SDL_Window* m_Window;

static vec4 m_BackgroundColor = (vec4){0.0f, 0.2f, 0.6f};

static SDL_KeyCode m_Keydown;
static SDL_KeyCode m_Keypressed;

static int m_Mouse3dtotalX = 0;
static int m_Mouse3dtotalY = 0;

static SDL_KeyCode m_MouseButtonDown;
static Uint8 m_MousePressed;
static Uint8 m_MouseDown;


static bool m_MouseMoved = false;
bool InitWindow(int width, int height, const char* title, Uint32 flags){
    #ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX);
    #endif
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fail("Couldn't initialize SDL! %s\n", SDL_GetError());
        return -1;
    }
    m_Window = SDL_CreateWindow(title,
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             width, height,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | flags);
    if (!m_Window) {
        fail("Couldn't Create SDL Window! %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    m_GlContext = SDL_GL_CreateContext(m_Window);
    if (!m_GlContext) {
        fail("Couldn't Create OpenGL Context! %s\n", SDL_GetError());
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fail("Couldn't Start GLAD!\n");
        SDL_GL_DeleteContext(m_GlContext);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
        return false;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    SetupCamera();
    return true;
}

bool IsKeyPressed(SDL_KeyCode key){
    if(m_Keypressed == key){
        return true;
    }
    return false;
}

bool IsKeyDown(SDL_KeyCode key){
    if(m_Keydown == key){
        m_Keydown = 0;
        return true;
    }
    return false;
}



void UpdateMousePositionFor3d() {  
    int deltaX, deltaY;
    SDL_GetRelativeMouseState(&deltaX, &deltaY);
    m_Mouse3dtotalX += deltaX;
    m_Mouse3dtotalY += deltaY;
}

int GetMousePositionFor3dX() {
    return m_Mouse3dtotalX;
}

int GetMousePositionFor3dY() {
    return m_Mouse3dtotalY;
}

int GetMousePositionX(){
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

int GetMousePositionY(){
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}


void LockMouse() {
    SDL_SetRelativeMouseMode(SDL_TRUE);
}


bool IsMouseButtonPressed(Uint8 mouse){
    if(m_MousePressed == mouse){
        m_MousePressed = -1;
        return true;
    } else return false;
}

bool DidMouseMove(){
    return m_MouseMoved;
}

int GetWindowWidth(){
    int h;
    int w;
    SDL_GetWindowSize(m_Window, &w, &h);
    return w;
}

int GetWindowHeight(){
    int h;
    int w;
    SDL_GetWindowSize(m_Window, &w, &h);
    return h;
}

void SetWindowTitle(char* title){
    SDL_SetWindowTitle(m_Window, title);
}

void SetWindowSize(vec2 size){
    SDL_SetWindowSize(m_Window, size[0], size[1]);
}


bool IsWindowOpen(){
    while (SDL_PollEvent(&m_Event)) {
        if (m_Event.type == SDL_QUIT) {
            m_Running = false;
        }
        if(m_Event.type == SDL_WINDOWEVENT){
            if(m_Event.window.event == SDL_WINDOWEVENT_RESIZED || m_Event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
            }
        }
        if(m_Event.type == SDL_KEYDOWN){
            m_Keypressed = m_Event.key.keysym.sym; 
            
        } else {
            if(m_Keydown == m_Event.key.keysym.sym){
                m_Keypressed = 0;
            }
        }
        if(m_Event.type == SDL_KEYDOWN){
            m_Keydown = m_Event.key.keysym.sym;   
        } 
        if(m_Event.type == SDL_MOUSEMOTION){
            m_MouseMoved = true;
        } else m_MouseMoved = false;
        if(m_Event.type == SDL_MOUSEBUTTONDOWN){
            m_MousePressed = m_Event.button.button;
            m_MouseButtonDown = true;
        } else m_MouseButtonDown = false;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glClearColor(m_BackgroundColor[0], m_BackgroundColor[1], m_BackgroundColor[2], m_BackgroundColor[3]);
    CalculateFrameRate();
    CalculateDeltaTime();
    UpdateCamera();
    return m_Running;
}

void ShutdownWindow(){
    m_Running = false;
}

void SwapWindow(){
    SDL_GL_SwapWindow(m_Window);
}

void CleanupWindow(){
    
    SDL_GL_DeleteContext(m_GlContext);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void ChangeBackground(vec4 color){
    glm_vec4_copy(color, m_BackgroundColor);
}

