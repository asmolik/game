
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

	int solverIterations;

	std::vector<Contact*> contacts;
	std::vector<Constraint*> constraints;

public:
	PhysicsEngine();

	void update(std::vector<RigidBody*>& objects);

	void resolveContact(Contact* contact);
	float calculateNormalImpulse(Contact* contact);
	float calculateTangentImpulse(Contact* contact, float normalImpulse);
	float handlePenetration(Contact* contact);

	void applyImpulses(Contact* contact, float normalImpulse, float tangentImpulse);

	void resolveCarTrackContact(Contact* contact);

	void addConstraint(Constraint* constraint);

	void setTimeStep(float dt);
	void setGravity(glm::vec3& g);
};

#endif