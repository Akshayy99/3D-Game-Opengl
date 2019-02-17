#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z);
    glm::vec3 position;
    double rotate;
    float radius1;
    float radius2;
    // double speedx;
    void draw(glm::mat4 VP);
    void tick();
    // glm::mat4 rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object1;
    VAO *object2;
    // VAO *object3;
};

#endif
