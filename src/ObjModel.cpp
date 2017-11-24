#include "objmodel.h"
#include "objloader.hpp"
#include "shader.hpp"
#include "shared.h"

// Constructor copy-pasta'd from HW2, reorganized.

ObjModel::ObjModel() {

    programID = LoadShaders( "data/vertex.glsl", "data/fragment.glsl");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenVertexArrays(1, &vertexbuffer);
	glGenVertexArrays(1, &uvbuffer);
	glGenVertexArrays(1, &nbuffer);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, nbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void ObjModel::loadObject(const char* objFile) {
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
}


// Credit to Jayson for helping me through this part.
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

void ObjModel::Render(glm::mat4 m, glm::mat4 v, glm::mat4 p) {
	glUseProgram(programID);
	glBindVertexArray(VertexArrayID);

	GLuint model = glGetUniformLocation(programID, "M");
	glUniformMatrix4fv(model, 1, GL_FALSE, &m[0][0]);

	GLuint view = glGetUniformLocation(programID, "V");
	glUniformMatrix4fv(view, 1, GL_FALSE, &v[0][0]);

	GLuint projection = glGetUniformLocation(programID, "P");
	glUniformMatrix4fv(projection, 1, GL_FALSE, &p[0][0]);

	glUniform1i(TextureID, 0);

	glActiveTexture(GL_TEXTURE1);

	glDrawArrays(GL_TRIANGLES, 0, vertex.size());
	

}