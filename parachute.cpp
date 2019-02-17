#include "parachute.h"
#include "main.h"

using namespace std;

Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    float n = 360;
    h_up = 30;
    killed = false;
    float theta = 2*3.14159/n;
    this->radius = 30;
    this->h_down = 50.0;
    int numTriangles = 360;

    // conical portion of the parachute
    GLfloat vertex_buffer_data3[numTriangles*9];
    for(int i=0;i<numTriangles;i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data3[i*9] = 0.0f;
        vertex_buffer_data3[i*9+1] = 0;
        vertex_buffer_data3[i*9+2] = 0;
        vertex_buffer_data3[i*9+3] = this->radius * cos(angleBefore);
        vertex_buffer_data3[i*9+4] = -this->h_up;
        vertex_buffer_data3[i*9+5] = this->radius * sin(angleBefore);
        vertex_buffer_data3[i*9+6] = this->radius * cos(angle);
        vertex_buffer_data3[i*9+7] = -this->h_up;
        vertex_buffer_data3[i*9+8] = this->radius * sin(angle);
    }
    // lower cube
    float len = 6.0;
    static const GLfloat vertex_buffer_data[] = {
        -len,-len-h_up-h_down,-len,
        -len,-len-h_up-h_down, len,
        -len, len-h_up-h_down, len,
        len, len-h_up-h_down,-len, 
        -len,-len-h_up-h_down,-len,
        -len, len-h_up-h_down,-len, 
        len,-len-h_up-h_down, len,
        -len,-len-h_up-h_down,-len,
        len,-len-h_up-h_down,-len,
        len, len-h_up-h_down,-len,
        len,-len-h_up-h_down,-len,
        -len,-len-h_up-h_down,-len,
        -len,-len-h_up-h_down,-len,
        -len, len-h_up-h_down, len,
        -len, len-h_up-h_down,-len,
        len,-len-h_up-h_down, len,
        -len,-len-h_up-h_down, len,
        -len,-len-h_up-h_down,-len,
        -len, len-h_up-h_down, len,
        -len,-len-h_up-h_down, len,
        len,-len-h_up-h_down, len,
        len, len-h_up-h_down, len,
        len,-len-h_up-h_down,-len,
        len, len-h_up-h_down,-len,
        len,-len-h_up-h_down,-len,
        len, len-h_up-h_down, len,
        len,-len-h_up-h_down, len,
        len, len-h_up-h_down, len,
        len, len-h_up-h_down,-len,
        -len, len-h_up-h_down,-len,
        len, len-h_up-h_down, len,
        -len, len-h_up-h_down,-len,
        -len, len-h_up-h_down, len,
        len, len-h_up-h_down, len,
        -len, len-h_up-h_down, len,
        len,-len-h_up-h_down, len
    };
    // string * 4
    float thic = 1;
    static const GLfloat vertex_buffer_data1[] = {
        radius-1, -h_up, thic,
        radius-1, -h_up, -thic,
        4, -h_down-h_up, thic,
        radius-1, -h_up, -thic,
        4, -h_down-h_up, thic,
        4,-h_down-h_up, -thic,

        -radius+1, -h_up, thic,
        -radius+1, -h_up, -thic,
        -4, -h_down-h_up, thic,
        -radius+1, -h_up, -thic,
        -4, -h_down-h_up, thic,
        -4,-h_down-h_up, -thic,

        thic, -h_up, -radius, 
        -thic, -h_up, -radius,
        thic, -h_up-h_down, -4, 
        -thic, -h_up, -radius,
        thic, -h_up-h_down, -4,
        -thic, -h_up-h_down, -4,

        thic, -h_up, radius, 
        -thic, -h_up, radius,
        thic, -h_up-h_down, 4, 
        -thic, -h_up, radius,
        thic, -h_up-h_down, 4,
        -thic, -h_up-h_down, 4
    };

    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data3,COLOR_JETBLACK,  GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, {247,247,247}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data1, COLOR_JETBLACK, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate1    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, -1, 0));
    // glm::mat4 rotate2    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -2, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Parachute::set_position(float x, float y, float z = 0) {
    this->position = glm::vec3(x, y, z);
}



