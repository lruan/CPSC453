#ifndef MVPMATRIX_H
#define MVPMATRIX_H

#include "shared.h"
#include "objmodel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

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