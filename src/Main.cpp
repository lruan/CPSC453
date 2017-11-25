/*
Main.CPP
CPSC 453 - Homework 3
Written by Mingxi (Logan) Ruan

Code Contributions and Sources listed where appropriate.
*/

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
int applyTexture = 1;
int applyAO = 0;

/*
    Key Callback FUnction
    Binds keys to GLFW conrols.
    Source:  http://www.opengl.org
*/

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    mvpchanging = true;
    if(key == GLFW_KEY_E && action == GLFW_PRESS) {
		rotationX = rotationX - 0.10f;
    }
    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
        rotationX = rotationX + 0.10f;
    }
    if(key == GLFW_KEY_T && action == GLFW_PRESS) {
        rotationY = rotationY - 0.10f;
    }
    if(key == GLFW_KEY_Y && action == GLFW_PRESS) {
        rotationY = rotationY + 0.10f;
    }
    if(key == GLFW_KEY_O && action == GLFW_PRESS) {
        rotationZ = rotationZ - 0.10f;
    }
    if(key == GLFW_KEY_P && action == GLFW_PRESS) {
        rotationZ = rotationZ + 0.10f;
    }
    if(key == GLFW_KEY_A && action == GLFW_PRESS) {
        applyTexture == 1 ? applyTexture = 0 : applyTexture = 1;
    }
    if(key == GLFW_KEY_X && action == GLFW_PRESS) {
        applyAO == 1 ? applyAO = 0 : applyAO = 1;
    }
    if(key == GLFW_KEY_UP && action == GLFW_PRESS) {
        fieldOfView >= 3.0f ? fieldOfView -= 2.5f : fieldOfView = fieldOfView;
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        fieldOfView <= 90.0f ? fieldOfView += 2.5f : fieldOfView = fieldOfView;
    }
}

/*
    Framebuffer Size Callback
    Relevant for Window Resizing cases.
    Source:  http://www.opengl.org
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// If the window size has changed the Viewport is updated.
	glViewport(0,0,width,height);
	mvpchanging = true;
}

/*
    Main Function
*/

int main(int argc, char* argv[]) {
    GLFWwindow* window = 0;
    
    if (argc != 4) {
        std::cerr << "Insufficient or Incorrect Command Line Arguments detected.\nPlease see the README file.\n";
        return 1;
    }

    const char* objFile = argv[1];
    const char* textureFile = argv[2];
    const char* aoFile = argv[3];

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
  	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    ObjModel object = ObjModel(objFile, textureFile, aoFile);

    if(object.width > 2 || object.height > 2) {
        float cartesian = 1.0f;
        object.width > object.height ? cartesian = object.width : cartesian = object.height;
        scaleFactor = scaleFactor / cartesian;
    }
    MVPMatrix MVP = MVPMatrix(object);

    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(mvpchanging) {

            // Credits to Jayson for helping me with the logic for model centering.
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

        object.Render(MVP.modelMatrix, MVP.viewMatrix, MVP.projectionMatrix, applyTexture, applyAO);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}