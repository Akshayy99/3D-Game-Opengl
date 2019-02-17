#include "main.h"

#ifndef BOUNDARY_H
#define BOUNDARY_H


class Boundary {
public:
    Boundary() {}
    Boundary(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float length;
    float thic;
    void draw(glm::mat4 VP);
private:
    VAO *object1;
};

#endif
