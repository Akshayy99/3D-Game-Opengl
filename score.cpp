#include "score.h"
#include "main.h"

Score::Score(float x, float y) {
    this->position = glm::vec3(x, y, -30);
    // this->rotate = glm::rotate((float) (180 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    this->gap = 0.07;
    this->len = 0.5;
    float zoom = 0.4;

    static const GLfloat vertex_buffer_data1[] = {
        zoom*(-len-gap), 0.0f, 29.0f,
        zoom*-gap, 0.0f, 29.0f,
        zoom*(-len-gap), zoom*-gap, 29.0f,

        zoom*(-len-gap), zoom*-gap, 29.0f,
        zoom*-gap, 0.0f, 29.0f,
        zoom*-gap, zoom*-gap, 29.0f
    };
    static const GLfloat vertex_buffer_data2[] = {
        zoom*-gap, zoom*-gap, 29.0f,
        zoom*-gap, zoom*(-len-gap), 29.0f,
        0.0f, zoom*-gap, 29.0f,

        0.0f, zoom*-gap, 29.0f,
        zoom*-gap, zoom*(-len-gap), 29.0f,
        0.0f, zoom*(-len-gap), 29.0f
    };
    static const GLfloat vertex_buffer_data3[] = {
        zoom*-gap, zoom*(-2*gap-len), 29.0f,
        zoom*-gap, zoom*(-2*len-2*gap), 29.0f,
        0.0f, zoom*(-2*gap-len), 29.0f,

        0.0f, zoom*(-2*gap-len), 29.0f,
        zoom*-gap, zoom*(-2*len-2*gap), 29.0f,
        0.0f, zoom*(-2*len-2*gap), 29.0f
    };
    static const GLfloat vertex_buffer_data4[] = {
        zoom*(-len-gap), zoom*(-2*len-2*gap), 29.0f,
        zoom*(-gap), zoom*(-2*len-2*gap), 29.0f,
        zoom*(-len-gap), zoom*(-2*len-3*gap), 29.0f,

        zoom*(-len-gap), zoom*(-2*len-3*gap), 29.0f,
        zoom*-gap, zoom*(-2*len-2*gap), 29.0f,
        zoom*-gap, zoom*(-2*len-3*gap), 29.0f
    };
    static const GLfloat vertex_buffer_data5[] = {
        zoom*(-len-2*gap), zoom*(-2*gap-len), 29.0f,
        zoom*(-len-2*gap), zoom*(-2*len-2*gap), 29.0f,
        zoom*(-len-gap), zoom*(-2*gap-len), 29.0f,

        zoom*(-len-2*gap), zoom*(-2*len-2*gap), 29.0f,
        zoom*(-len-gap), zoom*(-2*gap-len), 29.0f,
        zoom*(-len-gap), zoom*(-2*len-2*gap), 29.0f
    };
    static const GLfloat vertex_buffer_data6[] = {
        zoom*(-len-2*gap), zoom*-gap, 29.0f,
        zoom*(-len-gap), zoom*-gap, 29.0f,
        zoom*(-len-2*gap), zoom*(-len-gap), 29.0f,

        zoom*(-len-gap), zoom*-gap, 29.0f,
        zoom*(-len-2*gap), zoom*(-len-2*gap), 29.0f,
        zoom*(-len-gap), zoom*(-len-gap), 29.0f
    };
    static const GLfloat vertex_buffer_data7[] = {
        zoom*(-len-gap), zoom*(-len-gap), 29.0f,
        zoom*(-gap), zoom*(-len-gap), 29.0f,
        zoom*(-len-gap), zoom*(-len-2*gap), 29.0f,

        zoom*(-len-gap), zoom*(-len-2*gap), 29.0f,
        zoom*-gap, zoom*(-len-gap), 29.0f,
        zoom*-gap, zoom*(-len-2*gap), 29.0f
    }; 
    static const GLfloat vertex_buffer_data8[] = {
        0.0f, 0.0f, 29.0f,
        zoom*-0.05f, 0.0f, 29.0f, 
        zoom*-0.3f, zoom*-1.2f, 29.0f,

        zoom*-0.3f, zoom*-1.2f, 29.0f, 
        zoom*-0.05f, 0.0f, 29.0f,
        zoom*-0.3f, zoom*-1.0f, 29.0f,

        zoom*-0.3f, zoom*-1.2f, 29.0f,
        zoom*-0.3f, zoom*-1.0f, 29.0f,
        zoom*-0.55f, 0.0f, 29.0f,

        zoom*-0.3f, zoom*-1.2f, 29.0f,
        zoom*-0.6f, 0.0f, 29.0f,
        zoom*-0.55f, 0.0f, 29.0f
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, {0, 0, 0,}, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, {0, 0, 0,}, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, {0, 0, 0,}, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, {0, 0, 0,}, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, {0, 0, 0,}, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data6, {0, 0, 0,}, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data7, {0, 0, 0,}, GL_FILL);
    this->objectV = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data8, {0, 0, 0,}, GL_FILL);
}

void Score::draw(glm::mat4 VP, int a, int b, int c, int d, int e, int f, int g, int v) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(a) draw3DObject(this->object1);
    if(b) draw3DObject(this->object2);
    if(c) draw3DObject(this->object3);
    if(d) draw3DObject(this->object4);
    if(e) draw3DObject(this->object5);
    if(f) draw3DObject(this->object6);
    if(g) draw3DObject(this->object7);
    if(v) draw3DObject(this->objectV);
}
