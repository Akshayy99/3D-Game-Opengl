#include "fuelmeter.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Fuelmeter::Fuelmeter(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    // this->rotate = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    this->length = 1.2;
    this->breadth = 0.5;
    this->thic = 0.06;
    this->fuel = 1.2;

    static const GLfloat vertex_buffer_data1[] = {
        // 1
        thic, 0, 0,
        thic, thic, 0,
        thic+length, 0, 0,
        thic, thic, 0,
        thic+length, 0, 0,
        thic+length, thic, 0,
        // 2
        thic+length, thic, 0,
        2*thic+length, thic, 0,
        thic+length, thic+breadth, 0,
        2*thic+length, thic, 0,
        thic+length, thic+breadth, 0,
        2*thic+length, thic+breadth, 0,
        // 3
        thic, breadth+thic, 0,
        thic, breadth+2*thic, 0,
        thic+length, breadth+thic, 0,
        thic, breadth+2*thic, 0,
        thic+length, breadth+thic, 0,
        thic+length, breadth+2*thic, 0,
        // 4
        0, thic, 0,
        thic, thic, 0,
        0, thic+breadth, 0,
        thic, thic, 0,
        0, thic+breadth, 0,
        thic, thic+breadth, 0,
        //extra
        2*thic+length, thic+breadth/2-thic, 0,
        2*thic+length, thic+breadth/2+thic, 0,
        3*thic+length, thic+breadth/2-thic, 0,
        2*thic+length, thic+breadth/2+thic, 0,
        3*thic+length, thic+breadth/2-thic, 0,
        3*thic+length, thic+breadth/2+thic, 0
    };
    static const GLfloat vertex_buffer_data2[] = {
        thic, thic, 0,
        thic+fuel, thic, 0,
        thic+fuel, thic+breadth, 0,
        thic, thic, 0,
        thic+fuel, thic+breadth, 0,
        thic, thic+breadth, 0
    };

    this->object1 = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data1, COLOR_JETBLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, {255,111,105}, GL_FILL);
}

void Fuelmeter::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    Matrices.model[0][0] = length;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    translate[0][0] = fuel;
    Matrices.model = translate;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->fuel > 0){
        draw3DObject(this->object2);
    }
}

void Fuelmeter::tick() {
    // this->position.x -= speedx;
    if(fuel) this->fuel -= 0.0001;
}
