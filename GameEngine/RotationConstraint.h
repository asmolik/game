
#ifndef ROTATIONCONSTRAINT_H
#define ROTATIONCONSTRAINT_H

#include <glm/vec3.hpp>
#include "Constraint.h"

/*
A constraint for relative position between two bodies.
It allows second body's movement relative to first body's position.
Allowed movement can be specified separately for every axis (in first body's coordinates).
*/
class RotationConstraint : public Constraint
{
private:
	glm::vec3 position;
	glm::vec3 distanceMax;
	glm::vec3 distanceMin;

public:
	RotationConstraint();
	RotationConstraint(RigidBody* b1, RigidBody* b2);

	void solve();

	void setDistance(glm::vec3& position, glm::vec3& distanceMax, glm::vec3& distanceMin);
};

#endif