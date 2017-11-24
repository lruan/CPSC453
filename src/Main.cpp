#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "shared.h"
#include "stb_image.h"
#include "alice.h"
#include "objmodel.h"
#include "mvp.h"

#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

float scaleFactor = 1.0f;
float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;

float fieldOfView = 45.0f;

bool mvpchanging = true;

int main(int argc, char* argv[]) {
    GLFWwindow* window = 0;

    const char* objFile = argv[1];

    if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 960, 960, "HW3 - Model Renderer", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
    glfwMakeContextCurrent(window);
    
    /*
    if (argc != 4) {
        std::cerr << "Insufficient or Incorrect Command Line Arguments detected.\nPlease see the README file.\n";
        return 1;
    }
    */

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    ObjModel object = ObjModel();
    object.loadObject(objFile);

    std::cout << "loadObject successful\n";
    if(object.width > 2 || object.height > 2) {
        float cartesian = 1.0f;
        object.width > object.height ? cartesian = object.width : cartesian = object.height;
        scaleFactor = scaleFactor / cartesian;
    }
    MVPMatrix MVP = MVPMatrix(object);

    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(mvpchanging) {
            MVP.modelMatrix = glm::translate(MVP.modelMatrix, glm::vec3(object.objectCenter.at(0), 
                                                                        object.objectCenter.at(1), 
                                                                        object.objectCenter.at(2)));
            MVP.modelMatrix = glm::scale(MVP.modelMatrix, glm::vec3(scaleFactor));
            glm::mat4 euler = glm::eulerAngleXYZ(rotationX, rotationY, rotationZ);
            MVP.modelMatrix = MVP.modelMatrix * euler;
            MVP.modelMatrix = glm::translate(MVP.modelMatrix, glm::vec3(-object.objectCenter.at(0),
                                                                        -object.objectCenter.at(1),
                                                                        -object.objectCenter.at(2)));
            scaleFactor = 1.0f;
            rotationX = rotationY = rotationZ = 0.0f;

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            MVP.projectionMatrix = glm::perspective(glm::radians(fieldOfView), (float(width))/(float(height)), 0.1f, 100.0f);

            mvpchanging = false;
        }

        object.Render(MVP.modelMatrix, MVP.viewMatrix, MVP.projectionMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}