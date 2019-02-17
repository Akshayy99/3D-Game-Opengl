#include "main.h"

#ifndef NEEDLE_H    
#define NEEDLE_H


class Needle {
public:
    Needle() {}
    Needle(float x, float y, float angle);
    glm::vec3 position;
    float rot;
    float length;
    float thic;

    void draw(glm::mat4 VP);
    float rotate;
    glm::mat4 rotMatrix;
private:
    VAO *object;
};

#endif
