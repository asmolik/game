
#include "Plane.h"

Plane::Plane() : RigidBody(ObjectIDs::planeID) {}

void Plane::init(GLuint program)
{
	glGenBuffers(1, &Plane::vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, Plane::vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Plane::vertexPositions), Plane::vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &Plane::indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Plane::indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Plane::indexData), Plane::indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t normalsDataOffset = sizeof(float) * 3 * 4;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)normalsDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);


	glUseProgram(program);
	Plane::diffuseColorUnif = glGetUniformLocation(program, "diffuseColor");
	Plane::specularColorUnif = glGetUniformLocation(program, "specularColor");
	Plane::shininessFactorUnif = glGetUniformLocation(program, "shininessFactor");
	Plane::matrixUnif = glGetUniformLocation(program, "modelToCameraMatrix");
	glUseProgram(0);
}

std::vector<Contact*> Plane::generateContact(RigidBody* body)
{
	return std::vector<Contact*>();
}

void Plane::display(glutil::MatrixStack &matrix)
{
	//matrices
	glUniformMatrix4fv(Plane::matrixUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
	//material
	glUniform4f(Plane::diffuseColorUnif, 0.9f, 0.9f, 0.9f, 1.0f);
	glUniform4f(Plane::specularColorUnif, 0.25f, 0.25f, 0.25f, 1.0f);
	glUniform1f(Plane::shininessFactorUnif, 0.1f);

	glBindVertexArray(Plane::vao);
	glDrawElements(GL_TRIANGLES, sizeof(Plane::indexData) / sizeof(short), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

void Plane::displayLights(glutil::MatrixStack &matrix, glm::mat4& cameraTransform)
{

}

glm::vec3 Plane::getNormal()
{
	return normal;
}

void Plane::setNormal(glm::vec3& n)
{
	normal = n;
}

GLuint Plane::vertexBuffer = 0;
GLuint Plane::indexBuffer = 0;
GLuint Plane::vao = 0;
GLuint Plane::matrixUnif = 0;
GLuint Plane::worldMatrixUnif = 0;
GLuint Plane::diffuseColorUnif = 0;
GLuint Plane::specularColorUnif = 0;
GLuint Plane::shininessFactorUnif = 0;

const float Plane::vertexPositions[] = {
	//vertices
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 2000.0f,
	2000.0f, 0.0f, 2000.0f,
	2000.0f, 0.0f, 0.0f,
	//normals
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
};

const short Plane::indexData[] = {
	1, 0, 3,
	1, 3, 2,
};