
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

class RigidBody;

#include <glm/vec3.hpp>

class Constraint
{
protected:
	RigidBody* body1;
	RigidBody* body2;

public:
	Constraint();
	Constraint(RigidBody* b1, RigidBody* b2);

	void solve();
	void apply();
};

#endif