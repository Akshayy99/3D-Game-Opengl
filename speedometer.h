#include "main.h"

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H


class Speedometer {
public:
    Speedometer() {}
    Speedometer(float x, float y, float z);
    glm::vec3 position;
    float radius1;
    float radius2;
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
