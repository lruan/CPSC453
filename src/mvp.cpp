#include "shared.h"
#include "mvp.h"
#include "objmodel.h"

MVPMatrix::MVPMatrix(ObjModel obj) {
    projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    camera = glm::vec3(obj.objectCenter.at(0), obj.objectCenter.at(1), obj.objectCenter.at(2) + 3.0f);
    position = glm::vec3(obj.objectCenter.at(0), obj.objectCenter.at(1), obj.objectCenter.at(2));
    viewMatrix = glm::lookAt(camera, position, glm::vec3(0.0f, 1.0f, 1.0f));
    modelMatrix = glm::mat4(1.0f);
}