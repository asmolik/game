
#ifndef BOX_H
#define BOX_H

#include "RigidBody.h"
#include "Contact.h"

class Box : public RigidBody
{
private:
	glm::vec3 size;

	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	static GLuint matrixUnif;
	static GLuint colorUnif;

public:
	Box();

	static void init(GLuint program);

	Contact generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	glm::vec3 getSize();

	void setSize(glm::vec3& size);

	static const float vertexPositions[168];
	static const short indexData[36];
};

#endif