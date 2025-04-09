#include "player.h"
#include "engine/renderer.h"







void RenderPlayer(){
    // 0.0 will be the position for now, im just testing offsets
    // im also planning to make it so it returns the bottom offset of the legs and the top offset for collision detection

    
    // body
    RenderCube(0.4, (vec3){0.0, 0.0, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    RenderCube(0.4, (vec3){0.0, 0.0 - 0.4, -5.0}, (vec3){0.0, 0.0, 0.0}, false);

    // head
    RenderCube(0.3, (vec3){0.0, 0.0 + 0.3, -5.0}, (vec3){0.0, 0.0, 0.0}, false);

    // left arm
    RenderCube(0.2, (vec3){0.0 - 0.3, 0.0, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    RenderCube(0.2, (vec3){(0.0 - 0.3) - 0.2, 0.0, -5.0}, (vec3){0.0, 0.0, 0.0}, false);

    // right arm
    RenderCube(0.2, (vec3){0.0 + 0.3, 0.0, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    RenderCube(0.2, (vec3){(0.0 + 0.3) + 0.2, 0.0, -5.0}, (vec3){0.0, 0.0, 0.0}, false);

    // left leg
    RenderCube(0.1, (vec3){0.0 - 0.1, (0.0 - 0.4) - 0.25, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    RenderCube(0.1, (vec3){0.0 - 0.1, (0.0 - 0.4) - 0.35, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    RenderCube(0.1, (vec3){0.0 - 0.1, (0.0 - 0.4) - 0.45, -5.0}, (vec3){0.0, 0.0, 0.0}, false);

    // right leg
    RenderCube(0.1, (vec3){0.0 + 0.1, (0.0 - 0.4) - 0.25, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    RenderCube(0.1, (vec3){0.0 + 0.1, (0.0 - 0.4) - 0.35, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    RenderCube(0.1, (vec3){0.0 + 0.1, (0.0 - 0.4) - 0.45, -5.0}, (vec3){0.0, 0.0, 0.0}, false);
    
}