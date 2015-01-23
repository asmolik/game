
#include "Track.h"

Track::Track() : RigidBody(ObjectIDs::trackID) {}

void Track::init(GLuint program)
{
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

	size_t normalsDataOffset = sizeof(float) * 3 * 12;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)normalsDataOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);


	glUseProgram(program);
	Track::colorUnif = glGetUniformLocation(program, "theColor");
	Track::matrixUnif = glGetUniformLocation(program, "matrix");
	glUseProgram(0);
}

std::vector<Contact*> Track::generateContact(RigidBody* body)
{
	return std::vector<Contact*>();
}

void Track::display(glutil::MatrixStack &matrix)
{
	glUniformMatrix4fv(Track::matrixUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
	glUniform4f(Track::colorUnif, 0.3f, 0.3f, 0.3f, 1.0f);
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
GLuint Track::vao = 0;
GLuint Track::matrixUnif = 0;
GLuint Track::colorUnif = 0;

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