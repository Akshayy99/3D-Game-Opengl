#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 rotate = glm::mat4(1.0f);
    float yaw;
    float roll;
    float pitch;
    bool rise;
    bool fall;
    float speedy;
    float g1;
    float g2;
    float radius;
    float speed;
    float len;
    float fuel;
    float max_fuel;
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

#endif // PLANE_H
