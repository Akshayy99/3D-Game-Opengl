#include "main.h"

#ifndef PARACHTE_H
#define PARACHTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position;
    float h_up;
    float h_down;
    float radius;
    float r_ring;
    bool killed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    // void rise();
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // PARACHTE_H
