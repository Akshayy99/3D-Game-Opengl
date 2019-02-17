#include "compass.h"
#include "main.h"
#include<bits/stdc++.h>

using namespace std;

Compass::Compass(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->radius1 = 0.70;
    rotate = 0;
    this->radius2 = 0.76;
    float n = 360;
    float theta = 2*3.14159/n;
    int numTriangles = 720;
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
    float r1 = this->radius1, d = this->radius2-this->radius1;
    // d : thickness
    static const GLfloat vertex_buffer_data2[] = {
        d, 0, 0,
        0, r1, 0,
        -d, 0, 0,
        d, 0, 0,
        0, -r1, 0, 
        -d, 0, 0
    };
    // static const GLfloat vertex_buffer_data3[] = {
    //     d, 0, 0,
    //     0, -r1, 0, 
    //     -d, 0, 0
    // };
    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data1, COLOR_JETBLACK, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, COLOR_JETBLACK, GL_FILL);
    // this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, {0,0,0}, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    // cout << "a" << endl;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    
    glm::mat4 rotation = glm::rotate((float)(this->rotate), glm::vec3(0, 0, 1));
    Matrices.model *= (translate*rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // cout << "b" << endl;
    draw3DObject(this->object1);
    // cout << "c" << endl;

    draw3DObject(this->object2);
    // cout << "d" << endl;

    // draw3DObject(this->object3);
    // cout << "e" << endl;

}

void Compass::tick() {
    // this->position.x -= speedx;

}
