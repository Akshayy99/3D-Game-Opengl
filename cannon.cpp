#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 45;
    speed = 1;
    float len = 90.0;
    killed  = false;
    int n = 300;
    float theta = 2*3.14159/n;
    this->radius = 15.0;
    int numTriangles = 300;

    GLfloat vertex_buffer_data1[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data1[i*18] = this->radius * cos(angleBefore);
        vertex_buffer_data1[i*18+1] = this->radius * sin(angleBefore);
        vertex_buffer_data1[i*18+2] = len;
        vertex_buffer_data1[i*18+3] = this->radius * cos(angle);
        vertex_buffer_data1[i*18+4] = this->radius * sin(angle);
        vertex_buffer_data1[i*18+5] = len;
        vertex_buffer_data1[i*18+6] = this->radius * cos(angleBefore);
        vertex_buffer_data1[i*18+7] = this->radius * sin(angleBefore);
        vertex_buffer_data1[i*18+8] = 0.0f;
        vertex_buffer_data1[i*18+9] = this->radius * cos(angleBefore);
        vertex_buffer_data1[i*18+10] = this->radius * sin(angleBefore);
        vertex_buffer_data1[i*18+11] = 0.0f;
        vertex_buffer_data1[i*18+12] = this->radius * cos(angle);
        vertex_buffer_data1[i*18+13] = this->radius * sin(angle);
        vertex_buffer_data1[i*18+14] = len;
        vertex_buffer_data1[i*18+15] = this->radius * cos(angle);
        vertex_buffer_data1[i*18+16] = this->radius * sin(angle);
        vertex_buffer_data1[i*18+17] = 0.0f;

    }
    this->object = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data1, COLOR_JETBLACK, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    // this->rotation += speed;
}
