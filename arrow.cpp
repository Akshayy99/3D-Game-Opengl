#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->direction = glm::vec3(3,-3,-3);
    this->cur_dir = glm::vec3(0,1,0);
    this->rotate = 0;
    float len = 5;
    float breadth = 2.5;

    static const GLfloat vertex_buffer_data[] = {
        breadth/2, 0, 0,
        -breadth/2, 0, 0,
        breadth/2, -len, 0,
        -breadth/2, 0, 0,
        breadth/2, -len, 0,
        -breadth/2, -len, 0,

        breadth, 0, 0, 
        0, len/2, 0, 
        -breadth, 0, 0
    };
    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, {255,65,57}, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    glm::vec3 axis = glm::cross(glm::normalize(cur_dir), glm::normalize(direction));
    float angle = acos(glm::dot(glm::normalize(cur_dir), glm::normalize(direction)));
    glm::mat4 rotation = glm::rotate((float)angle, axis);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotation1  = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, -1));
    // glm::mat4 rotation3  = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // glm::mat4 rotation2  = glm::rotate((float)0, glm::vec3(0, 0, 1));
    // Matrices.model *= (translate*rotation1*rotation3*rotation2);
    Matrices.model *= (translate*rotation);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
    // this->rotation += speed;
}
