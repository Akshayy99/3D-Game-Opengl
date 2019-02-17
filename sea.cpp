#include "sea.h"
#include "main.h"

Sea::Sea(float x, float down, float z) {
    this->position = glm::vec3(x, down, z);

    float length = 10000.0;

    static const GLfloat vertex_buffer_data[] = {
        -length, down, -length,
        length,  down, -length,
        length,  down, length,

        length,  down, length,
        -length, down, -length,
        -length, down, length
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, {0,185,211}, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_2, COLOR_BROWN, GL_FILL);
    // this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_3, COLOR_RED, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
