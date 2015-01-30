
#include "Track.h"

Track::Track() : RigidBody(ObjectIDs::trackID) {}

void Track::init(GLuint program)
{
	glActiveTexture(GL_TEXTURE6);
	diffuseTexture = SOIL_load_OGL_texture("C:/Users/Olek/Documents/opengl/Road_Texture_Collection_Vol01/Road_0007_diffuse.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glActiveTexture(GL_TEXTURE7);
	specularTexture = SOIL_load_OGL_texture("C:/Users/Olek/Documents/opengl/Road_Texture_Collection_Vol01/Road_0007_specular.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	glBindTexture(GL_TEXTURE_2D, specularTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glActiveTexture(GL_TEXTURE8);
	normalTexture = SOIL_load_OGL_texture("C:/Users/Olek/Documents/opengl/Road_Texture_Collection_Vol01/Road_0007_bump.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	
	glGenBuffers(1, &Track::vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, Track::vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Track::vertexPositions), Track::vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &Track::indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Track::indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Track::indexData), Track::indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t normalsDataOffset = sizeof(float)* 3 * 12;
	size_t tangentsDataOffset = normalsDataOffset + sizeof(float) * 4 * 12;
	size_t textureDataOffset = tangentsDataOffset + sizeof(float)* 4 * 12;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)normalsDataOffset);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*)tangentsDataOffset);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)textureDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);


	glUseProgram(program);
	Track::diffuseTextureUnif = glGetUniformLocation(program, "diffuseColorSampler");
	Track::specularTextureUnif = glGetUniformLocation(program, "specularColorSampler");
	Track::normalTextureUnif = glGetUniformLocation(program, "normalSampler");
	Track::shininessFactorUnif = glGetUniformLocation(program, "shininessFactor");
	Track::matrixUnif = glGetUniformLocation(program, "modelToCameraMatrix");
	glUseProgram(0);
}

std::vector<Contact*> Track::generateContact(RigidBody* body)
{
	return std::vector<Contact*>();
}

void Track::display(glutil::MatrixStack &matrix)
{
	//matrices
	glUniformMatrix4fv(Track::matrixUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
	//material
	glUniform1f(Track::shininessFactorUnif, 0.6f);
	//texture
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	glUniform1i(diffuseTextureUnif, 6);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, specularTexture);
	glUniform1i(specularTextureUnif, 7);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glUniform1i(normalTextureUnif, 8);

	glBindVertexArray(Track::vao);
	glDrawElements(GL_TRIANGLES, sizeof(Track::indexData) / sizeof(short), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

glm::vec3 Track::getNormal()
{
	return normal;
}

void Track::setNormal(glm::vec3& n)
{
	normal = n;
}

GLuint Track::vertexBuffer = 0;
GLuint Track::indexBuffer = 0;
GLuint Track::diffuseTexture = 0;
GLuint Track::specularTexture = 0;
GLuint Track::normalTexture = 0;
GLuint Track::vao = 0;
GLuint Track::matrixUnif = 0;
GLuint Track::worldMatrixUnif = 0;
GLuint Track::diffuseTextureUnif = 0;
GLuint Track::specularTextureUnif = 0;
GLuint Track::normalTextureUnif = 0;
GLuint Track::shininessFactorUnif = 0;

const float Track::vertexPositions[] = {
	//vertices
	200.0f, 0.0f, 500.0f,
	210.0f, 0.0f, 510.0f,
	1700.0f, 0.0f, 500.0f,
	1690.0f, 0.0f, 510.0f,
	1700.0f, 0.0f, 700.0f,
	1690.0f, 0.0f, 690.0f,
	1300.0f, 0.0f, 700.0f,
	1290.0f, 0.0f, 690.0f,
	1300.0f, 0.0f, 1500.0f,
	1290.0f, 0.0f, 1490.0f,
	200.0f, 0.0f, 1500.0f,
	210.0f, 0.0f, 1490.0f,
	//normals
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	//tangents
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	//textures
	20.0f, 50.0f,
	21.0f, 51.0f,
	170.0f, 50.0f,
	169.0f, 51.0f,
	170.0f, 70.0f,
	169.0f, 69.0f,
	130.0f, 70.0f,
	129.0f, 69.0f,
	130.0f, 150.0f,
	129.0f, 149.0f,
	20.0f, 150.0f,
	21.0f, 149.0f,
};

const short Track::indexData[] = {
	0, 2, 3,
	0, 3, 1,
	2, 4, 5,
	2, 5, 3,
	4, 7, 5,
	4, 6, 7,
	6, 9, 7,
	6, 8, 9,
	8, 11, 9,
	8, 10, 11,
	10, 1, 11,
	10, 0, 1,
};