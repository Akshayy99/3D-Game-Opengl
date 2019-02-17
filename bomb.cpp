#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->downspeed = 0;
    yaw = 0;
    // float len = 6.0;
    g = 0.2;
    hit  = false;
    len = 2;
    static const GLfloat vertex_buffer_data[] = {
        -len,-len,-len,
        -len,-len, len,
        -len, len, len,
        len, len,-len, 
        -len,-len,-len,
        -len, len,-len, 
        len,-len, len,
        -len,-len,-len,
        len,-len,-len,
        len, len,-len,
        len,-len,-len,
        -len,-len,-len,
        -len,-len,-len,
        -len, len, len,
        -len, len,-len,
        len,-len, len,
        -len,-len, len,
        -len,-len,-len,
        -len, len, len,
        -len,-len, len,
        len,-len, len,
        len, len, len,
        len,-len,-len,
        len, len,-len,
        len,-len,-len,
        len, len, len,
        len,-len, len,
        len, len, len,
        len, len,-len,
        -len, len,-len,
        len, len, len,
        -len, len,-len,
        -len, len, len,
        len, len, len,
        -len, len, len,
        len,-len, len
    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, {76, 8, 19}, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, -1, 0));
    Matrices.model *= (translate*rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->object1);
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
    this->position.y -= this->downspeed;
    this->downspeed += this->g;
}
