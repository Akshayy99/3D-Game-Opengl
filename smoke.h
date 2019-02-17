#include "main.h"

#ifndef SMOKE_H
#define SMOKE_H


class Smoke {
public:
    Smoke() {}
    Smoke(float x, float y, float z);
    glm::vec3 position;
    bool scored;
    float r_in;
    float r_out;
    float thicc;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    // void rise();
    // double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // SMOKE_H
