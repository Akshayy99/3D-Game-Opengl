#include "missile.h"
#include "main.h"

Missile::Missile(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    // this->rotation = 0;
    yaw = 0;
    speed = 10;
    float len = 6.0;
    // g = 0.002;
    hit  = false;
    // radius = 0.3;
    len = 2;
    float len_head = 0.6;
    float n = 100;
    float theta = 2*3.14159/n;
    this->radius = 0.7;
    int numTriangles = 100;
    GLfloat vertex_buffer_data1[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data1[i*18] = this->radius * cos(angleBefore);
        vertex_buffer_data1[i*18+1] = this->radius * sin(angleBefore);
        vertex_buffer_data1[i*18+2] = -len;
        vertex_buffer_data1[i*18+3] = this->radius * cos(angle);
        vertex_buffer_data1[i*18+4] = this->radius * sin(angle);
        vertex_buffer_data1[i*18+5] = -len;
        vertex_buffer_data1[i*18+6] = this->radius * cos(angleBefore);
        vertex_buffer_data1[i*18+7] = this->radius * sin(angleBefore);
        vertex_buffer_data1[i*18+8] = 0.0f;
        vertex_buffer_data1[i*18+9] = this->radius * cos(angleBefore);
        vertex_buffer_data1[i*18+10] = this->radius * sin(angleBefore);
        vertex_buffer_data1[i*18+11] = 0.0f;
        vertex_buffer_data1[i*18+12] = this->radius * cos(angle);
        vertex_buffer_data1[i*18+13] = this->radius * sin(angle);
        vertex_buffer_data1[i*18+14] = -len;
        vertex_buffer_data1[i*18+15] = this->radius * cos(angle);
        vertex_buffer_data1[i*18+16] = this->radius * sin(angle);
        vertex_buffer_data1[i*18+17] = 0.0f;

    }
    GLfloat vertex_buffer_data3[numTriangles*18];
    for(int i=0;i<numTriangles;i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data3[i*9] = 0.0f;
        vertex_buffer_data3[i*9+1] = 0.0f;
        vertex_buffer_data3[i*9+2] = -len-len_head;
        vertex_buffer_data3[i*9+3] = this->radius * cos(angleBefore);
        vertex_buffer_data3[i*9+4] = this->radius * sin(angleBefore);
        vertex_buffer_data3[i*9+5] = 0.0f;
        vertex_buffer_data3[i*9+6] = this->radius * cos(angle);
        vertex_buffer_data3[i*9+7] = this->radius * sin(angle);
        vertex_buffer_data3[i*9+8] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data3, COLOR_BLACK, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, -1, 0));
    Matrices.model *= (translate*rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
    // this->downspeed -= this->g;
}
