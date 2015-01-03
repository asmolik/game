
#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() : gravity(glm::vec3(0, -9.80665, 0)) {}

void PhysicsEngine::update(std::vector<RigidBody*>& objects)
{
	//external forces
	for (RigidBody* object : objects)
	{
		object->setForce(gravity * object->getMass());
	}

	//collision detection - find contacts
	for (int i = 0; i < objects.size(); ++i)
	{
		for (int j = 0; j < objects.size(); ++j)
		{
			if (i == j)
				continue;
			Contact con = objects[i]->generateContact(objects[j]);
			if (con.getBody1() != 0 && con.getBody2() != 0)
				contacts.push_back(con);
		}
	}

	//handle penetrations
	for (Contact& contact : contacts)
	{
		handlePenetration(contact);
	}

	//resolve contacts
	for (Contact& contact : contacts)
	{
		resolveContact(contact);
	}

	//apply constraints
	for (Constraint* constraint : constraints)
	{
		//constraint->solve();
	}

	//integrate
	for (RigidBody* object : objects)
	{
		object->update(timeStep);
	}

	//clear contacts
	contacts.clear();
}

//https://en.wikipedia.org/wiki/Collision_response
void PhysicsEngine::resolveContact(Contact& contact)
{
	if (contact.getBody2()->getID() != ObjectIDs::trackID)
		return;

	if (contact.getTimeOfImpact() > timeStep /*|| contact.getDistance() < 0.001f*/)
		return;

	RigidBody* body1 = contact.getBody1();
	RigidBody* body2 = contact.getBody2();

	float e = body1->getRestitution() < body2->getRestitution() ?
		body1->getRestitution() : body2->getRestitution();

	//relative velocity
	//linear
	glm::vec3 relVel = body2->getVelocity() - body1->getVelocity();
	//angular
	relVel += glm::cross(body2->getAngularVelocity(), contact.getPoint2()) - glm::cross(body1->getAngularVelocity(), contact.getPoint1());

	float n = glm::dot(relVel, contact.getNormal());

	float d = body1->getInvMass() + body2->getInvMass();

	glm::vec3 tmp = glm::cross(body1->getInvInertia() * glm::cross(contact.getPoint1(), contact.getNormal()), contact.getPoint1());
	tmp += glm::cross(body2->getInvInertia() * glm::cross(contact.getPoint2(), contact.getNormal()), contact.getPoint2());

	d += glm::dot(tmp, contact.getNormal());

	//impulse
	float jm = std::max(-(1 + e) * n / d, 0.0f);

	/* speculative contact *//*
	float remove = -jm + (contact.getDistance() / timeStep) * (body1->getMass() + body2->getMass());

	if (remove < 0)
	{
		glm::vec3 jr = -contact.getNormal() * remove;
		body1->setMomentum(body1->getMomentum() - jr);
		body2->setMomentum(body2->getMomentum() + jr);
		body1->setAngularMomentum(body1->getAngularMomentum() - remove * body1->getInvInertia() * glm::cross(contact.getPoint1(), contact.getNormal()));
		body2->setAngularMomentum(body2->getAngularMomentum() + remove * body2->getInvInertia() * glm::cross(contact.getPoint2(), contact.getNormal()));
		return;
	}*/

	glm::vec3 j = contact.getNormal() * jm;

	if (body1->getInvMass() > 0)
	{
		body1->setMomentum(body1->getMomentum() - j);
		body1->setAngularMomentum(body1->getAngularMomentum() - jm * body1->getInvInertia() * glm::cross(contact.getPoint1(), contact.getNormal()));
	}
	if (body2->getInvMass() > 0)
	{
		body2->setMomentum(body2->getMomentum() + j);
		body2->setAngularMomentum(body2->getAngularMomentum() + jm * body2->getInvInertia() * glm::cross(contact.getPoint2(), contact.getNormal()));
	}

	////friction
	////http://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-friction-scene-and-jump-table--gamedev-7756

	//relativeVelocity = body2->getVelocity() - body1->getVelocity();

	//glm::vec3 tangent = relativeVelocity - (contact.getNormal() * glm::dot(relativeVelocity, contact.getNormal()));
	////tangent.normalizeThis(); idk

	//float jt = -glm::dot(tangent, relativeVelocity);
	//jt /= body1->getMass() + body2->getMass();

	//float mu = (body1->getStaticFriction() + body2->getStaticFriction()) / 2;

	//glm::vec3 frictionImpulse;
	//if (std::abs(jt) < j * mu)
	//	frictionImpulse = tangent * jt;
	//else
	//{
	//	mu = (body1->getDynamicFriction() + body2->getDynamicFriction()) / 2;
	//	frictionImpulse = tangent * (-j * mu);
	//}

	//body1->setVelocity(body1->getVelocity() + (frictionImpulse * (-body1->getInvMass())));
	//body2->setVelocity(body2->getVelocity() + (frictionImpulse * (body2->getInvMass())));
}

void PhysicsEngine::handlePenetration(Contact& contact)
{
	if (contact.getDistance() > 0)
		return;

	RigidBody* body1 = contact.getBody1();
	RigidBody* body2 = contact.getBody2();

	RigidBody* bodyToMove;
	if (body1->getInvMass() < body2->getInvMass())
		bodyToMove = body2;
	else
		bodyToMove = body1;

	bodyToMove->setPosition(bodyToMove->getPosition() + contact.getNormal() * contact.getDistance());

	////relative momentum (only linear)
	//glm::vec3 relMom = body2->getMomentum() - body1->getMomentum();

	////impulse
	//float jm = -glm::dot(relMom, contact.getNormal());

	////remove relative momentum
	//glm::vec3 j = contact.getNormal() * jm;

	//body1->setMomentum(body1->getMomentum() - j);
	//body2->setMomentum(body2->getMomentum() + j);

	////remove relative force
	//jm = glm::dot(body2->getForce() - body1->getForce(), contact.getNormal());

	//body1->applyForce(contact.getNormal() * jm);
	//body2->applyForce(contact.getNormal() * jm);

	////reverse relative velocities
	//jm = -glm::dot(body2->getVelocity() - body1->getVelocity(), contact.getNormal());

	//body1->setVelocity(body1->getVelocity() - contact.getNormal() * jm * 1.1f);
	//body2->setVelocity(body2->getVelocity() + contact.getNormal() * jm);
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