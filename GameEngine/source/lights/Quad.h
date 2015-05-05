
#pragma once

#include <GL/glew.h>
#include "glutil/glutil.h"

namespace Quad
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

	void display(glutil::MatrixStack& matrix);

	extern const float vertexPositions[12];
	extern const short indexData[6];
};