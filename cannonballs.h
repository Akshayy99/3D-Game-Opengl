#include "main.h"

#ifndef CANNONBALLS_H
#define CANNONBALLS_H


class Cannonballs {
public:
    Cannonballs() {}
    Cannonballs(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float downspeed;
    bool hit;
    float g;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif 