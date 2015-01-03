
#include "DistanceConstraint.h"

DistanceConstraint::DistanceConstraint() {}

DistanceConstraint::DistanceConstraint(RigidBody* b1, RigidBody* b2) : Constraint(b1, b2) {}

void DistanceConstraint::solve()
{

}

void DistanceConstraint::setDistance(float d)
{
	distance = d;
}