
#ifndef PLANE_H
#define PLANE_H

#include "RigidBody.h"
#include "Contact.h"

class Plane : public RigidBody
{
private:
	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	static GLuint matrixUnif;
	static GLuint colorUnif;

	glm::vec3 normal;

public:
	Plane();

	static void init(GLuint program);

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	glm::vec3 getNormal();

	void setNormal(glm::vec3& n);

	static const float vertexPositions[28];
	static const short indexData[6];
};

#endif