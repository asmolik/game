
#include "Box.h"

Box::Box() : RigidBody(ObjectIDs::boxID) {}

void Box::init(GLuint program)
{
	glGenBuffers(1, &Box::vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, Box::vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Box::vertexPositions), Box::vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &Box::indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Box::indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Box::indexData), Box::indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	size_t normalsDataOffset = sizeof(float)* 3 * 24;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)normalsDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);


	glUseProgram(program);
	Box::colorUnif = glGetUniformLocation(program, "theColor");
	Box::matrixUnif = glGetUniformLocation(program, "matrix");
	glUseProgram(0);
}

std::vector<Contact*> Box::generateContact(RigidBody* body)
{
	std::vector<Contact*> contacts;

	return contacts;
}

void Box::display(glutil::MatrixStack &matrix)
{
	glutil::PushStack push(matrix);

	matrix.Translate(current.position);
	matrix *= glm::mat4_cast(current.orientation);

	glUniformMatrix4fv(Box::matrixUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
	glUniform4f(Box::colorUnif, 237.0f / 255.0f, 28.0f / 255.0f, 36.0f / 255.0f, 1.0f);
	glBindVertexArray(Box::vao);
	glDrawElements(GL_TRIANGLES, sizeof(Box::indexData) / sizeof(short), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

glm::vec3 Box::getSize()
{
	return size;
}

void Box::setSize(glm::vec3& s)
{
	size = s;
}

GLuint Box::vertexBuffer = 0;
GLuint Box::indexBuffer = 0;
GLuint Box::vao = 0;
GLuint Box::matrixUnif = 0;
GLuint Box::colorUnif = 0;

const float Box::vertexPositions[] = {
	//vertices
	//left 0, 1, 2, 3
	-2.25f, -0.75f, 1.0f,
	2.25f, -0.75f, 1.0f,
	2.25f, 0.75f, 1.0f,
	-2.25f, 0.75f, 1.0f,
	//right 4, 5, 6, 7
	-2.25f, -0.75f, -1.0f,
	2.25f, -0.75f, -1.0f,
	2.25f, 0.75f, -1.0f,
	-2.25f, 0.75f, -1.0f,
	//front 8, 9, 10, 11
	-2.25f, -0.75f, 1.0f,
	-2.25f, -0.75f, -1.0f,
	-2.25f, 0.75f, -1.0f,
	-2.25f, 0.75f, 1.0f,
	//back 12, 13, 14, 15
	2.25f, -0.75f, 1.0f,
	2.25f, -0.75f, -1.0f,
	2.25f, 0.75f, -1.0f,
	2.25f, 0.75f, 1.0f,
	//top 16, 17, 18, 19
	-2.25f, 0.75f, 1.0f,
	2.25f, 0.75f, 1.0f,
	2.25f, 0.75f, -1.0f,
	-2.25f, 0.75f, -1.0f,
	//bottom 20, 21, 22, 23
	-2.25f, -0.75f, 1.0f,
	-2.25f, -0.75f, -1.0f,
	2.25f, -0.75f, -1.0f,
	2.25f, -0.75f, 1.0f,

	//normals
	//left
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	//right
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	//front
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	//back
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	//top
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	//bottom
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,

};

const short Box::indexData[] = {
	//left
	0, 3, 2,
	0, 2, 1,
	//right
	6, 7, 4,
	6, 4, 5,
	//front
	9, 10, 11,
	9, 11, 8,
	//back
	12, 15, 14,
	12, 14, 13,
	//top 
	16, 19, 18,
	16, 18, 17,
	//bottom
	20, 23, 22,
	20, 22, 21,

};