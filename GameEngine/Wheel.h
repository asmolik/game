
#ifndef WHEEL_H
#define WHEEL_H

#include "RigidBody.h"
#include "Contact.h"
#include <GL/glew.h>

class Wheel : public RigidBody
{
private:
	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	static GLuint matrixUnif;
	static GLuint colorUnif;

public:
	Wheel();

	static void init(GLuint program);

	Contact generateContact(RigidBody& body);

	void display(glutil::MatrixStack &matrix);

	static const float vertexPositions[2160];
	static const short indexData[362];
};

#endif