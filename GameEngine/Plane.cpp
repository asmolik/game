
#include "Plane.h"

Plane::Plane() : RigidBody(0) {}

Contact Plane::generateContact(RigidBody& body)
{
	return Contact();
}

void Plane::display(glutil::MatrixStack &matrix)
{

}

glm::vec3 Plane::getNormal()
{
	return normal;
}

void Plane::setNormal(glm::vec3& n)
{
	normal = n;
}

const float Plane::planeVertexPositions[] = {
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 2000.0f,
	2000.0f, 0.0f, 2000.0f,
	2000.0f, 0.0f, 0.0f,
};

const short Plane::planeIndexData[] = {
	1, 0, 3,
	1, 3, 2,
};