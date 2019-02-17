#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    float n = 300;
    height = 50;
    float theta = 2*3.14159/n;
    this->r_up = 8;
    this->r_down = 30.0;
    this->r_island = 60;
    int numTriangles = 300;

    // cylindrical portion of the volcano
    GLfloat vertex_buffer_data1[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data1[i*18] = this->r_up * cos(angleBefore);
        vertex_buffer_data1[i*18+1] = 0;
        vertex_buffer_data1[i*18+2] = this->r_up * sin(angleBefore);
        vertex_buffer_data1[i*18+3] = this->r_up * cos(angle);
        vertex_buffer_data1[i*18+4] = 0;
        vertex_buffer_data1[i*18+5] = this->r_up * sin(angle);
        vertex_buffer_data1[i*18+6] = this->r_down * cos(angleBefore);
        vertex_buffer_data1[i*18+7] = -height + 0;
        vertex_buffer_data1[i*18+8] = this->r_down * sin(angleBefore);
        vertex_buffer_data1[i*18+9] = this->r_down * cos(angleBefore);
        vertex_buffer_data1[i*18+10] = -height + 0;
        vertex_buffer_data1[i*18+11] = this->r_down * sin(angleBefore);
        vertex_buffer_data1[i*18+12] = this->r_up * cos(angle);
        vertex_buffer_data1[i*18+13] = 0;
        vertex_buffer_data1[i*18+14] = this->r_up * sin(angle);
        vertex_buffer_data1[i*18+15] = this->r_down * cos(angle);
        vertex_buffer_data1[i*18+16] = -height + 0;
        vertex_buffer_data1[i*18+17] = this->r_down * sin(angle);

    }
    // top
    GLfloat vertex_buffer_data3[numTriangles*9];
    for(int i=0;i<numTriangles;i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data3[i*9] = 0.0f;
        vertex_buffer_data3[i*9+1] = 0;
        vertex_buffer_data3[i*9+2] = 0;;
        vertex_buffer_data3[i*9+3] = this->r_up * cos(angleBefore);
        vertex_buffer_data3[i*9+4] = 0.0f;
        vertex_buffer_data3[i*9+5] = this->r_up * sin(angleBefore);
        vertex_buffer_data3[i*9+6] = this->r_up * cos(angle);
        vertex_buffer_data3[i*9+7] = 0.0f;
        vertex_buffer_data3[i*9+8] = this->r_up * sin(angle);
    }
    float d = 35;
    GLfloat vertex_buffer_data2[numTriangles*18];
    for(int i=0; i<numTriangles; i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data2[i*18] = this->r_island * cos(angleBefore);
        vertex_buffer_data2[i*18+1] = -d;
        vertex_buffer_data2[i*18+2] = this->r_island * sin(angleBefore);
        vertex_buffer_data2[i*18+3] = this->r_island * cos(angle);
        vertex_buffer_data2[i*18+4] = -d;
        vertex_buffer_data2[i*18+5] = this->r_island * sin(angle);
        vertex_buffer_data2[i*18+6] = this->r_island * cos(angleBefore);
        vertex_buffer_data2[i*18+7] = -d-height + 0;
        vertex_buffer_data2[i*18+8] = this->r_island * sin(angleBefore);
        vertex_buffer_data2[i*18+9] = this->r_island * cos(angleBefore);
        vertex_buffer_data2[i*18+10] = -d-height + 0;
        vertex_buffer_data2[i*18+11] = this->r_island * sin(angleBefore);
        vertex_buffer_data2[i*18+12] = this->r_island * cos(angle);
        vertex_buffer_data2[i*18+13] = -d;
        vertex_buffer_data2[i*18+14] = this->r_island * sin(angle);
        vertex_buffer_data2[i*18+15] = this->r_island * cos(angle);
        vertex_buffer_data2[i*18+16] = -d-height + 0;
        vertex_buffer_data2[i*18+17] = this->r_island * sin(angle);

    }
    GLfloat vertex_buffer_data4[numTriangles*9];
    for(int i=0;i<numTriangles;i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data4[i*9] = 0.0f;
        vertex_buffer_data4[i*9+1] = -d;
        vertex_buffer_data4[i*9+2] = 0;
        vertex_buffer_data4[i*9+3] = this->r_island * cos(angleBefore);
        vertex_buffer_data4[i*9+4] = -d;
        vertex_buffer_data4[i*9+5] = this->r_island * sin(angleBefore);
        vertex_buffer_data4[i*9+6] = this->r_island * cos(angle);
        vertex_buffer_data4[i*9+7] = -d;
        vertex_buffer_data4[i*9+8] = this->r_island * sin(angle);
    }
    this->object = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data1, COLOR_BROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data3, {240,56,20}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data4, {33,101,102}, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate1    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, -1, 0));
    // glm::mat4 rotate2    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -2, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Volcano::set_position(float x, float y, float z = 0) {
    this->position = glm::vec3(x, y, z);
}



