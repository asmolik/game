
#ifndef PLANE_H
#define PLANE_H

#include "RigidBody.h"
#include "Contact.h"

class Plane : public RigidBody
{
private:
	glm::vec3 normal;

public:
	Plane();

	Contact generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	glm::vec3 getNormal();

	void setNormal(glm::vec3& n);

	static const float planeVertexPositions[12];
	static const short planeIndexData[6];
};

#endif