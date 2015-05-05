
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include <glm/vec3.hpp>
#include "RigidBody.h"

class Constraint
{
protected:
	RigidBody* body1;
	RigidBody* body2;

public:
	Constraint();
	Constraint(RigidBody* b1, RigidBody* b2);

	virtual void solve() = 0;
	void apply();
};

#endif