#include <stdioh.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "shared.h"
#include "stb_image.h"
#include "alice.h"
#include "objmodel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

GLuint LoadShaders(const char* vertex_shader, const char* fragment_shader);
void Render(GLuint& shaders, )

int main(int argc, char* argv[]) {
    GLFWwindow* window = 0;

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

	window = glfwCreateWindow( 1920, 1080, "HW3 - Model Renderer", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}
    glfwMakeContextCurrent(window);
    
    if (argc != 4) {
        std::cerr << "Insufficient or Incorrect Command Line Arguments detected.\nPlease see the README file.\n";
        return 1;
    }

    glCLearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint programID = LoadShaders( "data/vertex.glsl", "data/fragment.glsl");

    OBJmodel object = OBJmodel();
}