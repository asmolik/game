
#include "Sphere.h"

void Sphere::init(GLuint program)
{
	glGenBuffers(1, &Sphere::vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, Sphere::vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Sphere::vertexPositions), Sphere::vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &Sphere::indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Sphere::indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Sphere::indexData), Sphere::indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &Sphere::vao);
	glBindVertexArray(Sphere::vao);

	glBindBuffer(GL_ARRAY_BUFFER, Sphere::vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Sphere::indexBuffer);

	glBindVertexArray(0);


	glUseProgram(program);
	Sphere::matrixUnif = glGetUniformLocation(program, "matrix");

	Sphere::positionTex = glGetUniformLocation(program, "positionTex");
	Sphere::diffuseTex = glGetUniformLocation(program, "diffuseTex");
	Sphere::specularTex = glGetUniformLocation(program, "specularTex");
	Sphere::normalTex = glGetUniformLocation(program, "normalTex");
	Sphere::textTex = glGetUniformLocation(program, "textTex");
	Sphere::shininessTex = glGetUniformLocation(program, "shininessTex");
	glUseProgram(0);
}

void Sphere::display(glutil::MatrixStack& matrix, float s)
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

	glBindVertexArray(Sphere::vao);
	glDrawElements(GL_TRIANGLE_STRIP, sizeof(Sphere::indexData) / sizeof(short), GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
}

GLuint Sphere::vertexBuffer = 0;
GLuint Sphere::indexBuffer = 0;
GLuint Sphere::vao = 0;
GLuint Sphere::matrixUnif = 0;
GLuint Sphere::positionTex = 0;
GLuint Sphere::diffuseTex = 0;
GLuint Sphere::specularTex = 0;
GLuint Sphere::textTex = 0;
GLuint Sphere::normalTex = 0;
GLuint Sphere::shininessTex = 0;

const float Sphere::vertexPositions[] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
};

const short Sphere::indexData[] = {
	0, 1, 2, 
	3, 7, 1, 
	5, 4, 7, 
	6, 2, 4, 
	0, 1
};