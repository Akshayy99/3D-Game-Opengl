#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float down, float z) {
    this->position = glm::vec3(x, down, z);
    taken = false;
    length = 200.0;

    static const GLfloat vertex_buffer_data[] = {
        // top
        -length, down, -length,
        length,  down, -length,
        length,  down, length,
        length,  down, length,
        -length, down, -length,
        -length, down, length
    };
    static const GLfloat vertex_buffer_data1[] = {
        // front
        length, down, length, 
        -length, down, length,
        -length, down-length, length,
        length, down-length, length,
        -length, down-length, length,
        length, down, length,
        // back
        length, down, -length, 
        -length, down, -length,
        -length, down-length, -length,
        length, down-length, -length,
        -length, down-length, -length,
        length, down, -length,
        // right
        length, down, length,
        length, down, -length,
        length, down-length, length,
        length, down-length, length,
        length, down, -length,
        length, down-length, -length,
        // left
        -length, down, length,
        -length, down, -length,
        -length, down-length, length,
        -length, down-length, length,
        -length, down, -length,
        -length, down-length, -length,        
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, {166,124,0}, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 8*3, vertex_buffer_data1, {191,155,48}, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}
