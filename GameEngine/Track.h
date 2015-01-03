
#ifndef TRACK_H
#define TRACK_H

#include "RigidBody.h"
#include "Contact.h"

class Track : public RigidBody
{
private:
	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	static GLuint matrixUnif;
	static GLuint colorUnif;

	glm::vec3 normal;

public:
	Track();

	static void init(GLuint program);

	Contact generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	glm::vec3 getNormal();

	void setNormal(glm::vec3& n);

	static const float vertexPositions[36];
	static const short indexData[36];
};

#endif