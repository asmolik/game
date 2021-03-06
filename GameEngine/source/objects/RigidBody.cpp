
#include "RigidBody.h"

RigidBody::RigidBody() : rigidBodyID(ObjectIDs::defaultID) {}

RigidBody::RigidBody(int id = 0) : rigidBodyID(id) {}

void RigidBody::update(float time)
{
	//current.velocity += current.invMass * current.accumulatedLinearImpulse;
	//current.angularVelocity += current.invInertia * current.accumulatedAngularImpulse;
	previous = current;
	Physics::integrateSIE(current, 0, time);
	current.accumulatedLinearImpulse = glm::vec3(0.0f);
	current.accumulatedAngularImpulse = glm::vec3(0.0f);
}

void RigidBody::integrateForces(float time)
{
	Physics::integrateForcesSIE(current, time);
}

void RigidBody::integrateVelocities(float time)
{
	Physics::integrateVelocitiesSIE(current, time);
	current.accumulatedLinearImpulse = glm::vec3(0.0f);
	current.accumulatedAngularImpulse = glm::vec3(0.0f);
}

void RigidBody::applyForce(glm::vec3& f)
{
	current.force += f;
}

void RigidBody::applyTorque(glm::vec3& t)
{
	current.torque += t;
}

void RigidBody::applyLinearImpulse(glm::vec3& i)
{
	current.velocity += current.invMass * i;
}

void RigidBody::applyAngularImpulse(glm::vec3& i)
{
	current.angularVelocity += current.invInertia * i;
}

void RigidBody::applyMomentum(glm::vec3& m)
{
	current.momentum += m;
}

void RigidBody::applyAngularMomentum(glm::vec3& m)
{
	current.angularMomentum += m;
}
 
glm::vec3 RigidBody::getFrontVector()
{
	return glm::vec3(1.0, 0.0, 0.0) * glm::conjugate(current.orientation);
}

glm::vec3 RigidBody::getRightVector()
{
	return glm::vec3(0.0, 0.0, 1.0) * glm::conjugate(current.orientation);
}

glm::vec3 RigidBody::getUpVector()
{
	return glm::vec3(0.0, 1.0, 0.0) * glm::conjugate(current.orientation);
}

int RigidBody::getID()
{
	return rigidBodyID;
}

glm::vec3 RigidBody::getPosition()
{
	return current.position;
}

glm::vec3 RigidBody::getMomentum()
{
	return current.momentum;
}

glm::vec3 RigidBody::getAngularMomentum()
{
	return current.angularMomentum;
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

glm::vec3 RigidBody::getAngularVelocity()
{
	return current.angularVelocity;
}

float RigidBody::getMass()
{
	return current.mass;
}

float RigidBody::getInvMass()
{
	return current.invMass;
}

glm::mat3 RigidBody::getInertia()
{
	return current.inertia;
}
glm::mat3 RigidBody::getInvInertia()
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

void RigidBody::rotate(glm::vec3& axis, float angleDeg)
{
	float angleRad = angleDeg * 3.1415926f / 180.0f;

	glm::vec3 a = glm::normalize(axis);

	a = a * sinf(angleRad / 2.0f);
	float scalar = cosf(angleRad / 2.0f);

	glm::fquat offset(scalar, a.x, a.y, a.z);

	current.orientation = current.orientation * offset;

	current.orientation = glm::normalize(current.orientation);
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

void RigidBody::setTorque(glm::vec3& t)
{
	current.torque = t;
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
	current.inertia = glm::mat3(i);
	if (i > 0.00001f)
		current.invInertia = glm::inverse(current.inertia);
	else
		current.invInertia = glm::mat3(0.0f);
}

void RigidBody::setInertia(glm::mat3& i)
{
	current.inertia = i;
	if (i[0].x > 0.00001f)
		current.invInertia = glm::inverse(i);
	else
		current.invInertia = glm::mat3(0.0f);
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

void RigidBody::accumulateLinearImpulse(glm::vec3& i)
{
	current.accumulatedLinearImpulse += i;
}

void RigidBody::accumulateAngularImpulse(glm::vec3& i)
{
	current.accumulatedAngularImpulse += i;
}

glm::vec3 RigidBody::getLinearImpulse()
{
	return current.accumulatedLinearImpulse;
}

glm::vec3 RigidBody::getAngularImpulse()
{
	return current.accumulatedAngularImpulse;
}

void RigidBody::clearAccumulatedImpulses()
{
	current.accumulatedLinearImpulse = glm::vec3(0.0f);
	current.accumulatedAngularImpulse = glm::vec3(0.0f);
}