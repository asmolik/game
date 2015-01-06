
#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include "RigidBody.h"
#include "Car.h"
#include "Contact.h"
#include "Constraint.h"

class PhysicsEngine
{
private:
	float timeStep;
	glm::vec3 gravity;

	std::vector<Contact*> contacts;
	std::vector<Constraint*> constraints;

public:
	PhysicsEngine();

	void update(std::vector<RigidBody*>& objects);
	void resolveContact(Contact* contact);
	void handlePenetration(Contact* contact);

	void resolveCarTrackContact(Contact* contact);

	void addConstraint(Constraint* constraint);

	void setTimeStep(float dt);
	void setGravity(glm::vec3& g);
};

#endif