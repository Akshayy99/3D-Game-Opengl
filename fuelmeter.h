#include "main.h"

#ifndef FUELMETER_H
#define FUELMETER_H


class Fuelmeter {
public:
    Fuelmeter() {}
    Fuelmeter(float x, float y, float z);
    glm::vec3 position;
    float length;
    float breadth;
    float thic;
    float fuel;
    // double speedx;
    void draw(glm::mat4 VP);
    void tick();
    glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object1;
    VAO *object2;
};

#endif
