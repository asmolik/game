
#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() : gravity(glm::vec3(0, -9.80665, 0)), solverIterations(4) {}

void PhysicsEngine::update(std::vector<RigidBody*>& objects)
{
	//integrate forces -> new velocities
	for (RigidBody* object : objects)
	{
		object->integrateForces(timeStep);
	}

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
}

//https://en.wikipedia.org/wiki/Collision_response
void PhysicsEngine::resolveContact(Contact* contact)
{
	if (contact->getBody2()->getID() != ObjectIDs::trackID)
		return;

	if (contact->getTimeOfImpact() > timeStep /*|| contact->getDistance() < 0.001f*/)
		return;

	RigidBody* body1 = contact->getBody1();
	RigidBody* body2 = contact->getBody2();

	float e = body1->getRestitution() < body2->getRestitution() ?
		body1->getRestitution() : body2->getRestitution();

	//relative velocity
	//linear
	glm::vec3 relVel = body2->getVelocity() - body1->getVelocity();
	//angular
	relVel += glm::cross(body2->getAngularVelocity(), contact->getPoint2()) - glm::cross(body1->getAngularVelocity(), contact->getPoint1());

	float n = glm::dot(relVel, contact->getNormal());

	float d = body1->getInvMass() + body2->getInvMass();

	glm::vec3 tmp = glm::cross(body1->getInvInertia() * glm::cross(contact->getPoint1(), contact->getNormal()), contact->getPoint1());
	tmp += glm::cross(body2->getInvInertia() * glm::cross(contact->getPoint2(), contact->getNormal()), contact->getPoint2());

	d += glm::dot(tmp, contact->getNormal());

	//impulse
	float jr = std::max(-(1 + e) * n / d, 0.0f);

	glm::vec3 j = contact->getNormal() * jr;
	glm::vec3 angj = jr * body1->getInvInertia() * glm::cross(contact->getPoint1(), contact->getNormal());

	contact->accumulateImpulse(jr);
	body1->applyLinearImpulse(-j);
	body1->applyAngularImpulse(-angj);

	angj = jr * body2->getInvInertia() * glm::cross(contact->getPoint2(), contact->getNormal());

	body2->applyLinearImpulse(j);
	body2->applyAngularImpulse(angj);

	//friction
	glm::vec3 tangent = relVel - (contact->getNormal() * glm::dot(relVel, contact->getNormal()));
	if (glm::length(tangent) < Physics::epsilon)
		return;
	tangent = glm::normalize(tangent);

	float jf = glm::dot(relVel * (body1->getMass() + body2->getMass()), tangent);

	float mu = (body1->getStaticFriction() + body2->getStaticFriction()) / 2;

	if (jf <= mu * jr)
		j = tangent * (-jf);
	else
	{
		mu = (body1->getDynamicFriction() + body2->getDynamicFriction()) / 2;
		j = tangent * (-jr * mu);
		jf = jr * mu;
	}

	body1->setVelocity(body1->getVelocity() - j * body1->getInvMass());
	body1->setAngularVelocity(body1->getAngularVelocity() + jf * body1->getInvInertia() * glm::cross(contact->getPoint1(), tangent));

	body2->setVelocity(body2->getVelocity() + j * body2->getInvMass());
	body2->setAngularVelocity(body2->getAngularVelocity() - jf * body2->getInvInertia() * glm::cross(contact->getPoint2(), tangent));
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
	body1->applyAngularImpulse(angularImpulse);

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
	if (point.x < 0 && point.z < 0)
		wheel = 1;
	else if (point.x < 0 && point.z > 0)
		wheel = 0;
	else if (point.x > 0 && point.z < 0)
		wheel = 3;
	else if (point.x > 0 && point.z > 0)
		wheel = 2;

	float normalImpulse = calculateNormalImpulse(contact);
	normalImpulse += handlePenetration(contact);

	contact->accumulateImpulse(normalImpulse);
	float impulseChange = contact->getAccumulatedImpulse() - tmpImpulse;

	applyImpulses(contact, impulseChange, 0);
	body1->accumulateLinearImpulse(-normalImpulse * contact->getNormal(), wheel);
}

float PhysicsEngine::handlePenetration(Contact* contact)
{
	if (contact->getDistance() >= -0.001f)
		return 0.0f;

	float b = 0.6f;
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