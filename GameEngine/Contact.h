
#ifndef CONTACT_H
#define CONTACT_H

class RigidBody;

#include <glm/vec3.hpp>

class Contact
{
protected:
	RigidBody* body1;
	RigidBody* body2;
	glm::vec3 normal;
	float distance;
	float timeOfImpact;

public:
	Contact();
	Contact(RigidBody* b1, RigidBody* b2, glm::vec3 normal, float distance, float timeOfImpact);
};

#endif