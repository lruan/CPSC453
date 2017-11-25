/*
mvp.H
CPSC 453 - Homework 3
Written by Mingxi (Logan) Ruan

Code Contributions and Sources listed where appropriate.
*/

#ifndef MVPMATRIX_H
#define MVPMATRIX_H

#include "shared.h"
#include "objmodel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

/*
    MVP Matrix Class, added as a new class to take it out of the
    Vertex Shader from HW2.
*/
class MVPMatrix {
    public:
    MVPMatrix(ObjModel o);

    glm::vec3 camera;
    glm::vec3 position;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 modelMatrix;
};

#endif