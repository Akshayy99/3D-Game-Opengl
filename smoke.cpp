#include "smoke.h"
#include "main.h"

Smoke::Smoke(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    float n = 300;
    thicc = 5;
    scored = false;
    float theta = 2*3.14159/n;
    this->r_in = 12;
    this->r_out = 14;
    int numTriangles = 300;

    // front ring
    GLfloat vertex_buffer_data1[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data1[i*18] = this->r_out * cos(angleBefore);
        vertex_buffer_data1[i*18+1] = this->r_out * sin(angleBefore);
        vertex_buffer_data1[i*18+2] = 0;
        vertex_buffer_data1[i*18+3] = this->r_out * cos(angle);
        vertex_buffer_data1[i*18+4] = this->r_out * sin(angle);
        vertex_buffer_data1[i*18+5] = 0;
        vertex_buffer_data1[i*18+6] = this->r_in * cos(angleBefore);
        vertex_buffer_data1[i*18+7] = this->r_in * sin(angleBefore);
        vertex_buffer_data1[i*18+8] = 0;
        vertex_buffer_data1[i*18+9] = this->r_in * cos(angleBefore);
        vertex_buffer_data1[i*18+10] = this->r_in * sin(angleBefore);
        vertex_buffer_data1[i*18+11] = 0;
        vertex_buffer_data1[i*18+12] = this->r_out * cos(angle);
        vertex_buffer_data1[i*18+13] = this->r_out * sin(angle);
        vertex_buffer_data1[i*18+14] = 0;
        vertex_buffer_data1[i*18+15] = this->r_in * cos(angle);
        vertex_buffer_data1[i*18+16] = this->r_in * sin(angle);
        vertex_buffer_data1[i*18+17] = 0;
    }
    // back ring
    GLfloat vertex_buffer_data2[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data2[i*18] = this->r_out * cos(angleBefore);
        vertex_buffer_data2[i*18+1] = this->r_out * sin(angleBefore);
        vertex_buffer_data2[i*18+2] = -thicc;
        vertex_buffer_data2[i*18+3] = this->r_out * cos(angle);
        vertex_buffer_data2[i*18+4] = this->r_out * sin(angle);
        vertex_buffer_data2[i*18+5] = -thicc;
        vertex_buffer_data2[i*18+6] = this->r_in * cos(angleBefore);
        vertex_buffer_data2[i*18+7] = this->r_in * sin(angleBefore);
        vertex_buffer_data2[i*18+8] = -thicc;
        vertex_buffer_data2[i*18+9] = this->r_in * cos(angleBefore);
        vertex_buffer_data2[i*18+10] = this->r_in * sin(angleBefore);
        vertex_buffer_data2[i*18+11] = -thicc;
        vertex_buffer_data2[i*18+12] = this->r_out * cos(angle);
        vertex_buffer_data2[i*18+13] = this->r_out * sin(angle);
        vertex_buffer_data2[i*18+14] = -thicc;
        vertex_buffer_data2[i*18+15] = this->r_in * cos(angle);
        vertex_buffer_data2[i*18+16] = this->r_in * sin(angle);
        vertex_buffer_data2[i*18+17] = -thicc;
    }
    GLfloat vertex_buffer_data3[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data3[i*18] = this->r_out * cos(angleBefore);
        vertex_buffer_data3[i*18+1] = this->r_out * sin(angleBefore);
        vertex_buffer_data3[i*18+2] = -thicc;
        vertex_buffer_data3[i*18+3] = this->r_out * cos(angle);
        vertex_buffer_data3[i*18+4] = this->r_out * sin(angle);
        vertex_buffer_data3[i*18+5] = -thicc;
        vertex_buffer_data3[i*18+6] = this->r_out * cos(angleBefore);
        vertex_buffer_data3[i*18+7] = this->r_out * sin(angleBefore);
        vertex_buffer_data3[i*18+8] = 0;
        vertex_buffer_data3[i*18+9] = this->r_out * cos(angleBefore);
        vertex_buffer_data3[i*18+10] = this->r_out * sin(angleBefore);
        vertex_buffer_data3[i*18+11] = 0;
        vertex_buffer_data3[i*18+12] = this->r_out * cos(angle);
        vertex_buffer_data3[i*18+13] = this->r_out * sin(angle);
        vertex_buffer_data3[i*18+14] = -thicc;
        vertex_buffer_data3[i*18+15] = this->r_out * cos(angle);
        vertex_buffer_data3[i*18+16] = this->r_out * sin(angle);
        vertex_buffer_data3[i*18+17] = 0;
    }

    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data1, {153,153,153}, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data2, {51,51,51}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data3, {153,153,153}, GL_FILL);
}

void Smoke::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    Matrices.model[0][0] = r_in/12;
    Matrices.model[1][1] = r_in/12;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Smoke::set_position(float x, float y, float z = 0) {
    this->position = glm::vec3(x, y, z);
}

void Smoke::tick()
{
    if(this->r_in < 15) r_in += 0.01;
    if(this->r_out < 18) r_out += 0.01;
    this->position.y += 0.6;
}

