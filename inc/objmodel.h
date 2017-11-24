#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "shared.h"
#include "alice.h"
#include <glm/glm.hpp>
#include <vector>

using std::vector;

class ObjModel {
	public:
		float width, height;

		ObjModel();

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

		void loadObject(const char* objFile);
		void loadTexture(const char* texFile);
		void loadOcclusion(const char* aoFile);

		void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, bool applyTexture, bool applyAO);
		
		vector<float> shapeDimension();
};

#endif
