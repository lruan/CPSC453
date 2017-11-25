/*
MVP.CPP
CPSC 453 - Homework 3
Written by Mingxi (Logan) Ruan

Code Contributions and Sources listed where appropriate.
*/

#include "shared.h"
#include "mvp.h"
#include "objmodel.h"

/*
    Just a constructor for MVP.h, moved out of
    Vertex Shader from HW2.
*/

MVPMatrix::MVPMatrix(ObjModel obj) {
    projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    camera = glm::vec3(obj.objectCenter.at(0), obj.objectCenter.at(1), obj.objectCenter.at(2) + 3.0f);
    position = glm::vec3(obj.objectCenter.at(0), obj.objectCenter.at(1), obj.objectCenter.at(2));
    viewMatrix = glm::lookAt(camera, position, glm::vec3(0.0f, 1.0f, 1.0f));
    modelMatrix = glm::mat4(1.0f);
}