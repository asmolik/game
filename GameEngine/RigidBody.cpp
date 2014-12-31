
#include "RigidBody.h"

RigidBody::RigidBody() : rigidBodyID(-1) {}

RigidBody::RigidBody(int id = -1) : rigidBodyID(id) {}

void RigidBody::update(float time)
{
	previous = current;
	Physics::integrate(current, 0, time);
}

void RigidBody::applyForce(glm::vec3 f)
{
	current.force += f;
}

void RigidBody::applyTorque(glm::vec3 f)
{
	current.torque += f;
}
 
glm::vec3 RigidBody::getFrontVector()
{
	return glm::vec3(-1.0, 0.0, 0.0) * current.orientation;
}

glm::vec3 RigidBody::getRightVector()
{
	return glm::vec3(0.0, 0.0, -1.0) * current.orientation;
}

glm::vec3 RigidBody::getUpVector()
{
	return glm::vec3(0.0, 1.0, 0.0) * current.orientation;
}

int RigidBody::getID()
{
	return rigidBodyID;
}

glm::vec3 RigidBody::getPosition()
{
	return current.position;
}

glm::vec3 RigidBody::getVelocity()
{
	return current.velocity;
}

glm::vec3 RigidBody::getForce()
{
	return current.force;
}

glm::quat RigidBody::getOrientation()
{
	return current.orientation;
}

float RigidBody::getMass()
{
	return current.mass;
}

float RigidBody::getInvMass()
{
	return current.invMass;
}

float RigidBody::getInertia()
{
	return current.inertia;
}
float RigidBody::getInvInertia()
{
	return current.invInertia;
}

float RigidBody::getDensity()
{
	return density;
}

float RigidBody::getRestitution()
{
	return restitution;
}

float RigidBody::getStaticFriction()
{
	return staticFriction;
}

float RigidBody::getDynamicFriction()
{
	return dynamicFriction;
}


void RigidBody::setID(int id)
{
	rigidBodyID = id;
}

void RigidBody::setPosition(glm::vec3& p)
{
	current.position = p;
}

void RigidBody::setMomentum(glm::vec3& m)
{
	current.momentum = m;
}

void RigidBody::setOrientation(glm::quat& o)
{
	current.orientation = o;
}

void RigidBody::setAngularMomentum(glm::vec3& m)
{
	current.angularMomentum = m;
}

void RigidBody::setVelocity(glm::vec3& v)
{
	current.velocity = v;
}

void RigidBody::setSpin(glm::quat& s)
{
	current.spin = s;
}

void RigidBody::setAngularVelocity(glm::vec3& v)
{
	current.angularVelocity = v;
}

void RigidBody::setForce(glm::vec3& f)
{
	current.force = f;
}

void RigidBody::zeroForce()
{
	current.force = glm::vec3();
}

void RigidBody::setMass(float m)
{
	current.mass = m;
	if (m > 0.00001f)
		current.invMass = 1 / m;
	else
		current.invMass = 0;
}

void RigidBody::setInertia(float i)
{
	current.inertia = i;
	if (i > 0.00001f)
		current.invInertia = 1 / i;
	else
		current.invInertia = 0;
}

void RigidBody::setDensity(float d)
{
	density = d;
}
void RigidBody::setRestitution(float r)
{
	restitution = r;
}

void RigidBody::setStaticFriction(float f)
{
	staticFriction = f;
}
void RigidBody::setDynamicFriction(float f)
{
	dynamicFriction = f;
}