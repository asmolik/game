
#include "Contact.h"

Contact::Contact() : body1(0), body2(0) {}

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

void Contact::set(RigidBody* b1, RigidBody* b2, glm::vec3& n, glm::vec3& p1, glm::vec3& p2, float d, float t)
{
	body1 = b1;
	body2 = b2;
	normal = n;
	point1 = p1;
	point2 = p2;
	distance = d;
	timeOfImpact = t;
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
