/*
objmodel.H
CPSC 453 - Homework 3
Written by Mingxi (Logan) Ruan

Code Contributions and Sources listed where appropriate.
*/

#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "shared.h"
#include "alice.h"
#include <glm/glm.hpp>
#include <vector>

using std::vector;

/*
	ObjModel Class

	Handles Rendering and Vertex Handling Logic.
*/
class ObjModel {
	public:
		float width, height;

		ObjModel(const char* objFile, const char* texFile, const char* aoFile);

//		bool LoadObjModel(const char * file);

		GLuint VertexArrayID, vertexbuffer, uvbuffer, nbuffer;
		GLuint programID;
	
		GLuint Texture;
		GLuint TextureID;

		GLuint AmbientOcclusion;
		GLuint AmbientOcclusionID;

		vector<float> objectCenter;

	    vector<glm::vec3> vertex;
	    vector<glm::vec2> uvvertex;
		vector<glm::vec3> n;

		void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, int useTexture, int useAO);
		
		vector<float> shapeDimension();
};

#endif
