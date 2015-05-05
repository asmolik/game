
#include "Contact.h"

Contact::Contact() : body1(0), body2(0), impulseAccumulator(0.0f) {}

Contact::Contact(RigidBody* b1, RigidBody* b2, glm::vec3 n, float d, float t) : body1(b1), body2(b2), normal(n), distance(d), timeOfImpact(t) {}

void Contact::setBody1(RigidBody* body)
{
	body1 = body;
}

void Contact::setBody2(RigidBody* body)
{
	body2 = body;
}

void Contact::setNormal(glm::vec3& n)
{
	normal = n;
}

void Contact::setDistance(float d)
{
	distance = d;
}

void Contact::setTimeOfImpact(float t)
{
	timeOfImpact = t;
}

void Contact::set(RigidBody* b1, RigidBody* b2, glm::vec3& n, glm::vec3& t,
	glm::vec3& p1, glm::vec3& p2, float d, float toi)
{
	body1 = b1;
	body2 = b2;
	normal = n;
	tangent = t;
	point1 = p1;
	point2 = p2;
	distance = d;
	timeOfImpact = toi;
}

RigidBody* Contact::getBody1()
{
	return body1;
}

RigidBody* Contact::getBody2()
{
	return body2;
}

glm::vec3 Contact::getNormal()
{
	return normal;
}

glm::vec3 Contact::getTangent()
{
	return tangent;
}

glm::vec3 Contact::getPoint1()
{
	return point1;
}

glm::vec3 Contact::getPoint2()
{
	return point2;
}

float Contact::getDistance()
{
	return distance;
}

float Contact::getTimeOfImpact()
{
	return timeOfImpact;
}

void Contact::accumulateImpulse(float i)
{
	impulseAccumulator += i;
	impulseAccumulator = std::max(impulseAccumulator, 0.0f);
}

float Contact::getAccumulatedImpulse()
{
	return impulseAccumulator;
}

void Contact::clampImpulse()
{
	impulseAccumulator = std::max(0.0f, impulseAccumulator);
}

void Contact::clearAccumulator()
{
	impulseAccumulator = 0.0f;
}