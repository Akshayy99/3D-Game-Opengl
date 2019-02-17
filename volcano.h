#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z);
    glm::vec3 position;
    float r_up;
    float r_down;
    float r_island;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    // void rise();
    // double speed;
private:
    VAO *object;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // VOLCANO_H
