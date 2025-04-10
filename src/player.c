#include "player.h"
#include "engine/external/cglm/vec3.h"
#include "engine/internals.h"
#include "engine/renderer.h"
#include "terrain.h"
#include <stdbool.h>






// vec3 pos, returns the leg and head pos
void RenderPlayer(vec3 pos, vec3 rotation, float* legpos, float* headpos){
    // 0.0 will be the position for now, im just testing offsets
    // im also planning to make it so it returns the bottom offset of the legs and the top offset for collision detection

    
    
    // animation code
    // float legspeed = 0.02;
    // float distance = 20;
    // static bool flip = false;
    // //leg[1]-=0.1;
    // if(flip == true){
    //     leg[0]-=legspeed;
    // } 
    // else{
    //     leg[0]+=legspeed;
    // } 
    // if(leg[0] >= distance) flip = true;
    // else if(leg[0] <= -distance) flip = false;
    //info("%f-%f\n", leg[0], leg[1]);
    
    // body
    RenderRectangularPrism(0.15, 0.3, 0.5, (vec3){pos[0], pos[1], pos[2]}, 
                    rotation, (vec3){1.0f, 0.0f, 1.0f}, false);

    // head
    RenderCube(0.3, (vec3){pos[0], pos[1] + 0.4, pos[2]}, rotation, false);

    // left hand
    RenderRectangularPrism(0.15, 0.15, 0.5, (vec3){pos[0] - 0.225, pos[1], pos[2]},
                    rotation, (vec3){1.0f, 0.0f, 0.0f}, false);

    // right hand
    RenderRectangularPrism(0.15, 0.15, 0.5, (vec3){pos[0] + 0.225, pos[1], pos[2]},
                    rotation, (vec3){1.0f, 0.0f, 0.0f}, false);

    // right leg
    
    RenderRectangularPrism(0.15, 0.15, 0.5, (vec3){pos[0] + 0.07, pos[1] - 0.5, pos[2]},
                    rotation, (vec3){1.0f, 1.0f, 0.0f}, false);
    
    // left leg
    vec3 opleg;
    glm_vec3_copy(rotation, opleg);
    glm_vec3_inv(opleg);
    RenderRectangularPrism(0.15, 0.15, 0.5, (vec3){pos[0] - 0.07, pos[1] - 0.5, pos[2]},
                    rotation, (vec3){1.0f, 1.0f, 0.0f}, false);
    if(legpos != NULL) *legpos = pos[1] - 0.5;
    if(headpos != NULL)*headpos = pos[1] + 0.4;
}



void RenderGolem(){
   
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