
#include "PositionConstraint.h"

PositionConstraint::PositionConstraint() {}

PositionConstraint::PositionConstraint(RigidBody* b1, RigidBody* b2) : Constraint(b1, b2) {}

void PositionConstraint::solve()
{
	glm::vec3 b1Pos = body1->getPosition();
	glm::vec3 b2Pos = body2->getPosition();
	//get b2 position relative to b1 position
	//translate b2
	b2Pos -= b1Pos;
	//rotate b2
	b2Pos = b2Pos * body1->getOrientation();
	
	b1Pos = glm::vec3(0.0f);

	glm::vec3 force = (position - b2Pos) * 800.0f;
	force -= (body2->getVelocity() - body1->getVelocity()) * 50.0f;
	force.y *= 0.6f;
	
	body1->applyForce(-force * body1->getMass() / 4.0f);
	body1->applyTorque(force * body1->getInvInertia() * glm::cross(b2Pos, position - b2Pos));
	body2->applyForce(force * body2->getMass());
}

void PositionConstraint::setDistance(glm::vec3& p, glm::vec3& dmax, glm::vec3& dmin)
{
	position = p;
	distanceMax = dmax;
	distanceMin = dmin;
}