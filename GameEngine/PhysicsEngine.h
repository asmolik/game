#pragma once

#include <vector>
#include "RigidBody.h"
#include "Car.h"
#include "Contact.h"
#include "Constraint.h"

class PhysicsEngine
{
protected:
	float timeStep;
	glm::vec3 gravity;

	int solverIterations;

	std::vector<Contact*> contacts;
	std::vector<Constraint*> constraints;

public:
	PhysicsEngine();

	/*
	Advances the simulation forward.
	1. Collision detection.
	2. Solver loop:
		2a. Solve contacts.
		2b. Solve constraints.
	3. Integrate velocities -> new positions.
	4. Set external forces
		-gravity
	5. Integrate forces -> new velocities.
	*/
	void update(std::vector<RigidBody*>& objects);

	/* 
	Resolve a contact between two bodies. 
	1. Get the accumulated impulse of the contact (0 at start).
	2a. Calculate impulse along the normal.
	2b. Add penetration handling to this impulse.
	3. Add this impulse with contact's accumulated impulse.
	4. Clamp the impulse (accumulated impulse has to be positive - separating the bodies).
	5. Calculate change of the impulse.
	6. Calculate impulse along the tangent.
	7. Apply the change of the normal impulse and the impulse along the tangent.
	*/
	void resolveContact(Contact* contact);
	/* Calculate impulse of the contact along the collision normal. */
	float calculateNormalImpulse(Contact* contact);
	/* Calculate impulse of the contact along the collision tangent. */
	float calculateTangentImpulse(Contact* contact, float normalImpulse);
	/* Handle penetration of two bodies. */
	float handlePenetration(Contact* contact);

	/* Apply impulses to both bodies from the contact. */
	void applyImpulses(Contact* contact, float normalImpulse, float tangentImpulse);

	/* Resolve a contact between a car and the terrain. */
	void resolveCarTrackContact(Contact* contact);

	void addConstraint(Constraint* constraint);

	void setTimeStep(float dt);
	void setGravity(glm::vec3& g);
};
