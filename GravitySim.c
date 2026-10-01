#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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


int drawGrid(int *ptrGrid){
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
    ptrGrid[addr] = c;
    return 0;
}


int main() {
    struct Planet earth;
    struct Planet sun;
    earth.mass = 1;
    sun.mass = 50;
    sun.pos.x = 0;
    sun.pos.y = 0;
    sun.pos.z = 0;
    earth.pos.x = 400;
    earth.pos.y = 0;
    earth.pos.z = 0;
    earth.velocity.y = 1;
    int *ptr = malloc(1024 * sizeof(char*)); // make the grid
    drawGrid(ptr);
    float earthX = 0;
    float earthY = 0;
    float sunX = 0;
    float sunY = 0;
    int i = 0;
    while (1) {
        i+=1;
        //printf("%f, %f\n", x, y);
        draw(ptr, earthX, earthY, ' ');
        draw(ptr, sunX, sunY, ' ');
        earth = processGravity(G, earth, sun);
        sun = processGravity(G, sun, earth);
        earth = processPosition(earth);
        sun = processPosition(sun);
        earthX = 32 * (earth.pos.x + 400)/800;
        earthY = 32 * (earth.pos.y + 400)/800;
        sunX = 32 * (sun.pos.x + 400)/800;
        sunY = 32 * (sun.pos.y + 400)/800;
        //printf("%f, %f\n", x, y);
        draw(ptr, earthX, earthY, 'E');
        draw(ptr, sunX, sunY, 'S');
        if (i % 10 == 0){
            renderGraphicsInAscii(ptr);
        }
    }
    free(ptr);
    return 0;
}
