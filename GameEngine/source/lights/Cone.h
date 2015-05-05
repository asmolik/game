
#pragma once

#include <GL/glew.h>
#include "glutil/glutil.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Cone
{
	extern GLuint vertexBuffer;
	extern GLuint indexBuffer;
	extern GLuint vao;
	extern GLuint matrixUnif;
	extern GLuint positionTex;
	extern GLuint diffuseTex;
	extern GLuint specularTex;
	extern GLuint textTex;
	extern GLuint normalTex;
	extern GLuint shininessTex;

	void init(GLuint program);

	void display(glutil::MatrixStack& matrix, float scale);

	extern const float vertexPositions[24];
	extern const short indexData[14];
};