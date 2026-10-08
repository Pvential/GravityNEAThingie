#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define G 9


struct Vec3 {
    float x;
    float y;
    float z;
};

struct ForceVector {
    struct Vec3 direction;
    float magnitude;
};

struct Planet {
    struct Vec3 pos;
    struct Vec3 velocity;
    struct Vec3 moveDirection;
    struct ForceVector force;
    double mass;
};

struct Planet processPosition(struct Planet planet) {
    planet.pos.x += planet.velocity.x;
    planet.pos.y += planet.velocity.y;
    planet.pos.z += planet.velocity.z;
    return planet;
}
struct Planet processGravity(float g, struct Planet planet, struct Planet otherPlanet) {
    float deltaX = planet.pos.x - otherPlanet.pos.x;
    float deltaY = planet.pos.y - otherPlanet.pos.y;
    float deltaZ = planet.pos.z - otherPlanet.pos.z;
    float distance = sqrt((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));

    
    planet.force.magnitude = -(g * planet.mass * otherPlanet.mass) / (distance*distance);
    planet.force.direction.x = deltaX / distance;
    planet.force.direction.y = deltaY / distance;
    planet.force.direction.z = deltaZ / distance;
    
    planet.velocity.x += (planet.force.direction.x * planet.force.magnitude) / planet.mass;
    planet.velocity.y += (planet.force.direction.y * planet.force.magnitude) / planet.mass;
    planet.velocity.z += (planet.force.direction.z * planet.force.magnitude) / planet.mass;
   
    return planet;
}
int findAddress(int x, int y){
    return (((y-1) * 32) + x);
}


int resetGrid(int *ptrGrid){
    // 1024 characters, 32 * 32 grid#
    int i;
    for(i=0; i < 1024; i++){
        ptrGrid[i] = ' ';
    }
    return 0; // gold experience requiem???
}

int renderGraphicsInAscii(int *ptrGrid){
    // 1024 characters, 32 * 32 grid
    int i;
    for(i=0; i < 1024; i++){
        printf("%c", ptrGrid[i]);
        if(i%32 == 0){
            printf("\n");
        }
    }
    return 0; // gold experience requiem???
}

int draw(int *ptrGrid, int x, int y, char c){
    
    int addr = findAddress(x, y);
    if (addr > 1024){ return 0; }
    ptrGrid[addr] = c;
    return 0;
}

float fixCoords(float num){
    return (32 * (num + 400)/800);
}


int main() {
    // registering --objects-- structs
    struct Planet earth;
    struct Planet sun;

    // start conditions
    earth.mass = 10;
    sun.mass = 50;
    earth.pos.x = 200;
    earth.pos.y = 100;
    //earth.velocity.y = 1;
    earth.velocity.x = -1;

    // ooo scary pointers!!!!
    int *ptr = malloc(1024 * sizeof(char*)); // make the grid

    int i = 0;
    while (1) {
        i+=1;
        resetGrid(ptr);
        
        //sun = processGravity(G, sun, earth);
        earth = processGravity(G, earth, sun);
        
        earth = processPosition(earth);
        //sun = processPosition(sun);
        
        draw(ptr, fixCoords(earth.pos.x), fixCoords(earth.pos.y), 'E');
        draw(ptr, fixCoords(sun.pos.x), fixCoords(sun.pos.y), 'S');
        if (i % 10 == 0){
            renderGraphicsInAscii(ptr);
            usleep(0.1 * (1000000));
        }
    }
    free(ptr);
    return 0;
}
