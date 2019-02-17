#include "main.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(float x, float y);
    // float radius1;
    // float radius2;
    float gap;
    float len;
    glm::vec3 position;
    void draw(glm::mat4 VP,int a, int b, int c, int d, int e, int f, int g, int v);
    // glm::mat4 rotate;
    // glm::mat4 rotMatrix;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *objectV;
};

#endif
