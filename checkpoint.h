#include "main.h"

#ifndef CHECKPOINT_H    
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float down);
    glm::vec3 position;
    bool taken;
    float length;
    void draw(glm::mat4 VP);
private:
    VAO *object;
    VAO *object1;
};

#endif
