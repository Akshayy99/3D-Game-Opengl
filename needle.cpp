#include "needle.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Needle::Needle(float x, float y, float angle) {
    this->position = glm::vec3(x, y, -10);
    this->rotate = 180;
    this->rot = angle;
    // this->rotate = glm::rotate((float) (rot * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->length = 0.64;
    this->thic = 0.06;
    // this->fuel = 1.2;
    float r = 0.70;
    static const GLfloat vertex_buffer_data1[] = {
        0, 0, 0,
        length, 0, 0,
        length, thic, 0,
        0, 0, 0,
        length, thic, 0,
        0, thic, 0,

        length, 0, 0,
        length, thic, 0,
        r, thic/2, 0
    };

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data1, COLOR_JETBLACK, GL_FILL);
}

void Needle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1    = glm::rotate((float) (this->rot * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rotate2   = glm::rotate((float) (180*M_PI/180.0f), glm::vec3(0,1,0));
    Matrices.model *= (translate * rotate1 * rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
