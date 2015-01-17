
#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() : gravity(Physics::gravity), solverIterations(4) {}

void PhysicsEngine::update(std::vector<RigidBody*>& objects)
{
	//collision detection - find contacts
	for (int i = 0; i < objects.size(); ++i)
	{
		for (int j = 0; j < objects.size(); ++j)
		{
			if (i == j)
				continue;
			std::vector<Contact*> con = objects[i]->generateContact(objects[j]);
			for (Contact* c : con)
			{
				if (c->getBody1() != 0 && c->getBody2() != 0)
					contacts.push_back(c);
			}
		}
	}

	//solver
	for (int i = 0; i < solverIterations; ++i)
	{
		//resolve contacts
		for (Contact* contact : contacts)
		{
			float tmp = contact->getAccumulatedImpulse();
			if (contact->getBody1()->getID() == ObjectIDs::carID &&
				contact->getBody2()->getID() == ObjectIDs::trackID)
				resolveCarTrackContact(contact);
			else
				resolveContact(contact);
		}

		//apply constraints
		for (Constraint* constraint : constraints)
		{
			constraint->solve();
		}
	}

	//integrate velocities -> new positions
	for (RigidBody* object : objects)
	{
		object->integrateVelocities(timeStep);
	}

	//clear contacts
	for (Contact* contact : contacts)
	{
		delete contact;
	}
	contacts.clear();

	//clear torque and force
	for (RigidBody* object : objects)
	{
		object->setForce(gravity * object->getMass());
		object->setTorque(glm::vec3(0.0f));
	}

	//integrate forces -> new velocities
	for (RigidBody* object : objects)
	{
		object->integrateForces(timeStep);
	}

}

//https://en.wikipedia.org/wiki/Collision_response
void PhysicsEngine::resolveContact(Contact* contact)
{
	if (contact->getBody2()->getID() != ObjectIDs::trackID)
		return;

	if (contact->getTimeOfImpact() > timeStep /*|| contact->getDistance() < 0.001f*/)
		return;

	float tmpImpulse = contact->getAccumulatedImpulse();

	RigidBody* body1 = contact->getBody1();
	RigidBody* body2 = contact->getBody2();

	float normalImpulse = calculateNormalImpulse(contact);
	normalImpulse += handlePenetration(contact);

	contact->accumulateImpulse(normalImpulse);
	contact->clampImpulse();
	float impulseChange = contact->getAccumulatedImpulse() - tmpImpulse;

	float tangentImpulse = calculateTangentImpulse(contact, normalImpulse);

	applyImpulses(contact, impulseChange, tangentImpulse);

}

float PhysicsEngine::calculateNormalImpulse(Contact* contact)
{
	RigidBody* body1 = contact->getBody1();
	RigidBody* body2 = contact->getBody2();

	float e = body1->getRestitution() < body2->getRestitution() ?
		body1->getRestitution() : body2->getRestitution();

	//relative velocity
	//linear
	glm::vec3 relVel = body2->getVelocity() - body1->getVelocity();
	//angular
	relVel += glm::cross(body2->getAngularVelocity(), contact->getPoint2()) - glm::cross(body1->getAngularVelocity(), contact->getPoint1());

	if (glm::length(relVel) < 0.05f)
		e = 0.0f;

	float n = glm::dot(relVel, contact->getNormal());

	float d = body1->getInvMass() + body2->getInvMass();

	glm::vec3 tmp = glm::cross(body1->getInvInertia() * glm::cross(contact->getPoint1(), contact->getNormal()), contact->getPoint1());
	tmp += glm::cross(body2->getInvInertia() * glm::cross(contact->getPoint2(), contact->getNormal()), contact->getPoint2());

	d += glm::dot(tmp, contact->getNormal());

	//impulse
	return -(1 + e) * n / d;
}

float PhysicsEngine::calculateTangentImpulse(Contact* contact, float normalImpulse)
{
	RigidBody* body1 = contact->getBody1();
	RigidBody* body2 = contact->getBody2();

	//relative velocity
	//linear
	glm::vec3 relVel = body2->getVelocity() - body1->getVelocity();
	//angular
	relVel += glm::cross(body2->getAngularVelocity(), contact->getPoint2()) - glm::cross(body1->getAngularVelocity(), contact->getPoint1());

	float tangentImpulse = glm::dot(relVel * (body1->getMass() + body2->getMass()), contact->getTangent());

	float mu = (body1->getStaticFriction() + body2->getStaticFriction()) / 2;

	if (tangentImpulse <= mu * normalImpulse)
		return tangentImpulse;
	else
	{
		mu = (body1->getDynamicFriction() + body2->getDynamicFriction()) / 2;
		return normalImpulse * mu;
	}
}

void PhysicsEngine::applyImpulses(Contact* contact, float normalImpulse, float tangentImpulse)
{
	RigidBody* body1 = contact->getBody1();
	RigidBody* body2 = contact->getBody2();

	glm::vec3 linearImpulse = contact->getNormal() * normalImpulse;
	glm::vec3 angularImpulse = normalImpulse * body1->getInvInertia() * glm::cross(contact->getPoint1(), contact->getNormal());
	linearImpulse += contact->getTangent() * tangentImpulse;
	angularImpulse += tangentImpulse * body1->getInvInertia() * glm::cross(contact->getPoint1(), contact->getTangent());

	body1->applyLinearImpulse(-linearImpulse);
	body1->applyAngularImpulse(-angularImpulse);

	angularImpulse = normalImpulse * body2->getInvInertia() * glm::cross(contact->getPoint2(), contact->getNormal());
	angularImpulse += tangentImpulse * body2->getInvInertia() * glm::cross(contact->getPoint2(), contact->getTangent());

	body2->applyLinearImpulse(linearImpulse);
	body2->applyAngularImpulse(angularImpulse);
}

void PhysicsEngine::resolveCarTrackContact(Contact* contact)
{
	if (contact->getTimeOfImpact() > timeStep /*|| contact->getDistance() < 0.001f*/)
		return;

	float tmpImpulse = contact->getAccumulatedImpulse();

	Car* body1 = (Car*)contact->getBody1();
	RigidBody* body2 = contact->getBody2();

	//which wheel hit
	int wheel;
	glm::vec3 point = contact->getPoint1();
	if (point.x > 0 && point.z < 0)
		wheel = 0;
	else if (point.x > 0 && point.z > 0)
		wheel = 1;
	else if (point.x < 0 && point.z < 0)
		wheel = 2;
	else if (point.x < 0 && point.z > 0)
		wheel = 3;

	float normalImpulse = calculateNormalImpulse(contact);
	normalImpulse += handlePenetration(contact);

	contact->accumulateImpulse(normalImpulse);
	contact->clampImpulse();
	float impulseChange = contact->getAccumulatedImpulse() - tmpImpulse;

	applyImpulses(contact, impulseChange, 0);
	body1->accumulateLinearImpulse(-normalImpulse * contact->getNormal(), wheel);
}

float PhysicsEngine::handlePenetration(Contact* contact)
{
	if (contact->getDistance() >= -0.0001f)
		return 0.0f;
	if (contact->getDistance() < -0.1f)
	{
		int i = 0;
		++i;
	}

	float b = 5.5f;
	return -b / timeStep * contact->getDistance();
}

void PhysicsEngine::addConstraint(Constraint* c)
{
	constraints.push_back(c);
}

void PhysicsEngine::setTimeStep(float dt)
{
	timeStep = dt;
}

void PhysicsEngine::setGravity(glm::vec3& g)
{
	gravity = g;
}