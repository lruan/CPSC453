/*
objmodel.H
CPSC 453 - Homework 3
Written by Mingxi (Logan) Ruan

Code Contributions and Sources listed where appropriate.
*/

#include "objmodel.h"
#include "objloader.hpp"
#include "shared.h"

#include <GLFW/glfw3.h>

/*
	Constructor copy-pasta'd from HW2, reorganized.
	Expanded to include logic for loading texture and ao files in addition to objfile.
*/

ObjModel::ObjModel(const char* objFile, const char* texFile, const char* aoFile) {

    programID = LoadShaders("data/vertex.glsl", "data/fragment.glsl");

  	glGenVertexArrays(1, &VertexArrayID);

	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &uvbuffer);
	glGenBuffers(1, &nbuffer);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Load Object File

	if(!loadOBJ(objFile, vertex, uvvertex, n))
	{
		std::cerr << "Error Loading Object File!" << std::endl;
		return;
	}

	shapeDimension();

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvvertex.size() * sizeof(glm::vec2), &uvvertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
	glBufferData(GL_ARRAY_BUFFER, n.size() * sizeof(glm::vec3), &n[0], GL_STATIC_DRAW);

	// Load Texture File
	// Code nearly identical to HW2 logic.
	
	ALICE aliceTexture = ALICE();
	aliceTexture.loadImage(texFile);

	Texture = LoadTexture(aliceTexture);
	TextureID = glGetUniformLocation(programID, "textureSampler");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);

	// Load Ambient Occlusion File
	// Code nearly identical to HW2 logic.

	ALICE aliceAO = ALICE();
	aliceAO.loadImage(aoFile);

	AmbientOcclusion = LoadTexture(aliceAO);
	AmbientOcclusionID = glGetUniformLocation(programID, "aoSampler");

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, AmbientOcclusion);
}
/*

	Dimension Shaping to fit Model within Viewer Frame.
	Hardcoded comparisons to set new object center based on averaged coordinate values.

Credit to Jayson for helping me through this part.

*/
vector<float> ObjModel::shapeDimension() {
	objectCenter.clear();

	float minimumX = vertex.at(0).x;
	float maximumX = vertex.at(0).x;
	float minimumY = vertex.at(0).y;
	float maximumY = vertex.at(0).y;
	float minimumZ = vertex.at(0).z;
	float maximumZ = vertex.at(0).z;

	for (unsigned int i = 0; i < vertex.size(); i++) {
		float x = vertex.at(i).x;
		float y = vertex.at(i).y;
		float z = vertex.at(i).z;

		if(x < minimumX)
		{
			minimumX = x;
		}
		else if(x > maximumX)
		{
			maximumX = x;
		}

		if(y < minimumY)
		{
			minimumY = y;
		}
		else if(y > maximumY)
		{
			maximumY = y;
		}

		if(z < minimumZ)
		{
			minimumZ = z;
		}
		else if(z > maximumZ)
		{
			maximumZ = z;
		}
	}

	objectCenter.push_back((minimumX + maximumX) / 2);
	objectCenter.push_back((minimumY + maximumY) / 2);
	objectCenter.push_back((minimumZ + maximumZ) / 2);

	width = maximumX - minimumX;
	height = maximumY - minimumY;

	return objectCenter;
}


/*
	Rendering function.
	Logic taken from a huge chunk of HW2's main loop.
*/
void ObjModel::Render(glm::mat4 m, glm::mat4 v, glm::mat4 p, int useTexture, int useAO) {
	glUseProgram(programID);
	glBindVertexArray(VertexArrayID);

 	GLuint textureApplies = glGetUniformLocation(programID, "textureApplies");
 	glUniform1i(textureApplies, useTexture);
  
  	GLuint aoApplies = glGetUniformLocation(programID, "aoApplies");
  	glUniform1i(aoApplies, useAO);

	GLuint model = glGetUniformLocation(programID, "M");
	glUniformMatrix4fv(model, 1, GL_FALSE, &m[0][0]);

	GLuint view = glGetUniformLocation(programID, "V");
	glUniformMatrix4fv(view, 1, GL_FALSE, &v[0][0]);

	GLuint projection = glGetUniformLocation(programID, "P");
	glUniformMatrix4fv(projection, 1, GL_FALSE, &p[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(TextureID, 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, AmbientOcclusion);
	glUniform1i(AmbientOcclusionID, 1);

	glDrawArrays(GL_TRIANGLES, 0, vertex.size());
}

/*
	Texture loading function for Texture and AO files.
	Entirely taken from HW2'S logic.
	An additional one-color channel is added to account for AO.
*/
GLuint LoadTexture(ALICE alice) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	    if(alice.channel == 3)
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, alice.width, alice.height, 0, GL_RGB, GL_UNSIGNED_BYTE, alice.pixels);
		else if(alice.channel == 4)
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, alice.width, alice.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, alice.pixels);
    	else if(alice.channel == 1)
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, alice.width, alice.height, 0, GL_RED, GL_UNSIGNED_BYTE, alice.pixels);

	return texture;
}