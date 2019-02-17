#include "speedometer.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Speedometer::Speedometer(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    // this->rotate = 180;
    this->radius1 = 0.70;
    this->radius2 = 0.76;
    float n = 360;
    float theta = 2*3.14159/n;
    int numTriangles = 360;
    GLfloat vertex_buffer_data1[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data1[i*18] = this->radius1 * cos(angleBefore);
        vertex_buffer_data1[i*18+1] = -this->radius1 * sin(angleBefore);
        vertex_buffer_data1[i*18+2] = 0;
        vertex_buffer_data1[i*18+3] = this->radius2 * cos(angle);
        vertex_buffer_data1[i*18+4] = -this->radius2 * sin(angle);
        vertex_buffer_data1[i*18+5] = 0;
        vertex_buffer_data1[i*18+6] = this->radius2 * cos(angleBefore);
        vertex_buffer_data1[i*18+7] = -this->radius2 * sin(angleBefore);
        vertex_buffer_data1[i*18+8] = 0;
        vertex_buffer_data1[i*18+9] = this->radius1 * cos(angleBefore);
        vertex_buffer_data1[i*18+10] = -this->radius1 * sin(angleBefore);
        vertex_buffer_data1[i*18+11] = 0;
        vertex_buffer_data1[i*18+12] = this->radius1 * cos(angle);
        vertex_buffer_data1[i*18+13] = -this->radius1 * sin(angle);
        vertex_buffer_data1[i*18+14] = 0;
        vertex_buffer_data1[i*18+15] = this->radius2 * cos(angle);
        vertex_buffer_data1[i*18+16] = -this->radius2 * sin(angle);
        vertex_buffer_data1[i*18+17] = 0;

    }
    float r2 = this->radius2, d = this->radius2-this->radius1;
    // d : thickness
    static const GLfloat vertex_buffer_data2[] = {
        r2, 0, 0,
        r2, -d, 0,
        -r2, 0, 0,

        -r2, 0, 0,
        -r2, -d, 0,
        r2, -d, 0
    };
    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data1, {0,0,0}, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, {0,0,0}, GL_FILL);
}

void Speedometer::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    
    // glm::mat4 rotation = glm::rotate((float) (this->rotate * M_PI / 180.0f), glm::vec3(0, -1, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Speedometer::tick() {
    // this->position.x -= speedx;

}
