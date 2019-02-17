#include "boundary.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Boundary::Boundary(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->length = 5;
    this->thic = 0.06;
    this->rotation = 0;
    static const GLfloat vertex_buffer_data1[] = {
        0, 0, 0,
        0, thic, 0,
        -length, 0, 0,
        -length, 0, 0,
        0, thic, 0,
        -length, thic, 0
    };
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_JETBLACK, GL_FILL);
}

void Boundary::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

