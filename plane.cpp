#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->yaw = 0;
    this->roll = 0;
    this->pitch = 0;
    float n = 300;
    len = 10.0;
    float len2 = 13.0;
    float len_head = 2.0;
    speed = 3;
    rise = false;
    fall = false;
    speedy = 0;
    g1 = 0.002;
    g2 = 0.0005;
    max_fuel = 20;
    fuel = max_fuel;
    float theta = 2*3.14159/n;
    this->radius = 1.5;
    int numTriangles = 300;

    // cylindrical portion of the plane
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
    // wings of the plane
    static GLfloat vertex_buffer_data2[] = {
        0.0f, 0.6f*this->radius, 0.3f*len,
        0.0f, 0.6f*this->radius, 0.6f*len,
        -len2/2, -0.6f*this->radius, 0.6f*len,

        0.0f, 0.6f*this->radius, 0.6f*len,
        -len2/2, -0.6f*this->radius, 0.6f*len,
        -(8/15.0f)*len2, -0.6f*this->radius, 0.7f*len,

        0.0f, 0.6f*this->radius, 0.3f*len,
        0.0f, 0.6f*this->radius, 0.6f*len,
        len2/2, -0.6f*this->radius, 0.6f*len,

        0.0f, 0.6f*this->radius, 0.6f*len,
        len2/2, -0.6f*this->radius, 0.6f*len,
        (8/15.0f)*len2, -0.6f*this->radius, 0.7f*len
    };
    // conical head of the plane
    GLfloat vertex_buffer_data3[numTriangles*18];
    for(int i=0;i<numTriangles;i++)
    {
        float angleBefore = theta * (180 + i);
        float angle = angleBefore + theta;

        vertex_buffer_data3[i*9] = 0.0f;
        vertex_buffer_data3[i*9+1] = -0.2f;
        vertex_buffer_data3[i*9+2] = -len_head;
        vertex_buffer_data3[i*9+3] = this->radius * cos(angleBefore);
        vertex_buffer_data3[i*9+4] = this->radius * sin(angleBefore);
        vertex_buffer_data3[i*9+5] = 0.0f;
        vertex_buffer_data3[i*9+6] = this->radius * cos(angle);
        vertex_buffer_data3[i*9+7] = this->radius * sin(angle);
        vertex_buffer_data3[i*9+8] = 0.0f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, numTriangles*6, vertex_buffer_data1, {22,29,116}, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, {38,54,111}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, numTriangles*3, vertex_buffer_data3, {38,54,111}, GL_FILL);

}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate1    = glm::rotate((float) (this->yaw * M_PI / 180.0f), glm::vec3(0, -1, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, -1));
    glm::mat4 rotate3    = glm::rotate((float) (this->pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -2, 0));
    Matrices.model *= (translate*rotate1*rotate3*rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Plane::set_position(float x, float y, float z = 0) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick() {
    this->fuel -= 0.001;
    this->position.z -= this->speed * cos(this->yaw * M_PI / 180.0f) * cos(this->pitch * M_PI /180.0f);
    this->position.x += this->speed * sin(this->yaw * M_PI / 180.0f);
    this->position.y += this->speed * sin(this->pitch * M_PI / 180.0f);
    float alt_default = 0;
    // if(this->rise){
        // this->position.y += 1;
    // }
    if(this->fall){
        this->position.y -= 1;
    }

    if(this->position.y > alt_default && !this->rise && !this->fall)
        this->position.y -= speedy;
    if(this->position.y < alt_default && !this->rise && !this->fall)
        // this->position.y = alt_default;
    if(this->position.y > alt_default + 10 && !this->rise)
    {
        this->speedy -= this->g1;
    }
    else if(this->position.y >= alt_default && !this->rise)
    {
        this->speedy -= this->g2;
    }

    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

