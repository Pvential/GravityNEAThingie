#include <stdio.h>

#include <math.h>

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
    while (1) {
        earth = processGravity(G, earth, sun);
        sun = processGravity(G, sun, earth);
        earth = processPosition(earth);
        sun = processPosition(sun);
        printf("%f, %f, %f\n", earth.pos.x, earth.pos.y, earth.pos.z);
    }
    return 0;
}
