
#include "Quad.h"

void Quad::init(GLuint program)
{
	glGenBuffers(1, &Quad::vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, Quad::vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Quad::vertexPositions), Quad::vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &Quad::indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Quad::indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Quad::indexData), Quad::indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &Quad::vao);
	glBindVertexArray(Quad::vao);

	glBindBuffer(GL_ARRAY_BUFFER, Quad::vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Quad::indexBuffer);

	glBindVertexArray(0);


	glUseProgram(program);
	Quad::matrixUnif = glGetUniformLocation(program, "matrix");
	glUseProgram(0);
}

void Quad::display(glutil::MatrixStack& matrix)
{
	glutil::PushStack push(matrix);

	glUniformMatrix4fv(Quad::matrixUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));

	glBindVertexArray(Quad::vao);
	glDrawElements(GL_TRIANGLES, sizeof(Quad::indexData) / sizeof(short), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

GLuint Quad::vertexBuffer = 0;
GLuint Quad::indexBuffer = 0;
GLuint Quad::vao = 0;
GLuint Quad::matrixUnif = 0;

const float Quad::vertexPositions[] = {
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
};

const short Quad::indexData[] = {
	0, 1, 2,
	3, 2, 1,
};