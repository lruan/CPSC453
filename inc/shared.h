#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <sstream>

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <vector>
using std::vector;

#define GLFW_INCLUDE_GLCOREARB

#define GL_GLEXT_PROTOTYPES

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLuint LoadShaders(const char* vertex, const char* fragment);

#endif