
#include "Cone.h"

void Cone::init(GLuint program)
{
	glGenBuffers(1, &Cone::vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, Cone::vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cone::vertexPositions), Cone::vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &Cone::indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Cone::indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Cone::indexData), Cone::indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &Cone::vao);
	glBindVertexArray(Cone::vao);

	glBindBuffer(GL_ARRAY_BUFFER, Cone::vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Cone::indexBuffer);

	glBindVertexArray(0);


	glUseProgram(program);
	Cone::matrixUnif = glGetUniformLocation(program, "matrix");

	Cone::positionTex = glGetUniformLocation(program, "positionTex");
	Cone::diffuseTex = glGetUniformLocation(program, "diffuseTex");
	Cone::specularTex = glGetUniformLocation(program, "specularTex");
	Cone::normalTex = glGetUniformLocation(program, "normalTex");
	Cone::textTex = glGetUniformLocation(program, "textTex");
	Cone::shininessTex = glGetUniformLocation(program, "shininessTex");
	glUseProgram(0);
}

void Cone::display(glutil::MatrixStack& matrix, float s)
{
	glutil::PushStack push(matrix);

	matrix.Scale(s);

	glUniformMatrix4fv(matrixUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
	glUniform1i(positionTex, 0);
	glUniform1i(diffuseTex, 1);
	glUniform1i(specularTex, 2);
	glUniform1i(normalTex, 3);
	glUniform1i(textTex, 4);
	glUniform1i(shininessTex, 5);

	glBindVertexArray(Cone::vao);
	glDrawElements(GL_TRIANGLE_STRIP, sizeof(Cone::indexData) / sizeof(short), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

GLuint Cone::vertexBuffer = 0;
GLuint Cone::indexBuffer = 0;
GLuint Cone::vao = 0;
GLuint Cone::matrixUnif = 0;
GLuint Cone::positionTex = 0;
GLuint Cone::diffuseTex = 0;
GLuint Cone::specularTex = 0;
GLuint Cone::textTex = 0;
GLuint Cone::normalTex = 0;
GLuint Cone::shininessTex = 0;

const float Cone::vertexPositions[] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
};

const short Cone::indexData[] = {
	0, 1, 2,
	3, 7, 1,
	5, 4, 7,
	6, 2, 4,
	0, 1
};