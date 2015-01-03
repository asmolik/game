
#ifndef DISTANCECONSTRAINT_H
#define DISTANCECONSTRAINT_H

class RigidBody;

#include <glm/vec3.hpp>
#include "Constraint.h"

class DistanceConstraint : public Constraint
{
private:
	float distance;

public:
	DistanceConstraint();
	DistanceConstraint(RigidBody* b1, RigidBody* b2);

	void solve();

	void setDistance(float distance);
};

#endif