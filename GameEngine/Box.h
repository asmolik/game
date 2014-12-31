
#ifndef BOX_H
#define BOX_H

#include "RigidBody.h"
#include "Contact.h"

class Box : public RigidBody
{
private:
	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	static GLuint matrixUnif;
	static GLuint colorUnif;

public:
	Box();

	static void init(GLuint program);

	Contact generateContact(RigidBody& body);

	void display(glutil::MatrixStack &matrix);

	static const float vertexPositions[168];
	static const short indexData[36];
};

#endif