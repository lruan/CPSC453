#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "shared.h"
#include "stb_image.h"
#include "alice.h"
#include "objmodel.h"
#include "mvp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

GLuint LoadShaders(const char* vertex_shader, const char* fragment_shader);

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

    MVPMatrix MVP = MVPMatrix(object);

    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        object.Render(MVP.modelMatrix, MVP.viewMatrix, MVP.projectionMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}