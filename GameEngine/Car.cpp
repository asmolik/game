
#include "Car.h"

Car::Car() : RigidBody(ObjectIDs::carID) { box.setSize(glm::vec3(4.5f, 1.5f, 2.0f)); }

/*Car::Car(glm::vec3& p, glm::vec3& n, float m, float i = 0, float d = 0,
	float r = 0, float sf = 0, float df = 0) : RigidBody(0, p, glm::vec3(), m, i, d, r, sf, df) {}*/

void Car::update(float time)
{
	rl.update(time);
	rr.update(time);
	fl.update(time);
	fr.update(time);

	box.update(time);
}

void Car::accelerate()
{
	rl.applyTorque(rl.getRightVector() * 1000.0f);
	rr.applyTorque(rr.getRightVector() * 1000.0f);
}

void Car::breaks()
{
	fl.applyTorque(-fl.getRightVector() * 1000.0f);
	fr.applyTorque(-fr.getRightVector() * 1000.0f);
	rl.applyTorque(-rl.getRightVector() * 1100.0f);
	rr.applyTorque(-rr.getRightVector() * 1100.0f);
}

void Car::turnLeft()
{
	fl.applyTorque(fl.getUpVector());
	fr.applyTorque(fr.getUpVector());
}

void Car::turnRight()
{
	fl.applyTorque(-fl.getUpVector());
	fr.applyTorque(-fr.getUpVector());
}

Contact Car::generateContact(RigidBody* body)
{
	return Contact();
}

void Car::display(glutil::MatrixStack &matrix)
{
	box.display(matrix);

	fl.display(matrix);
	fr.display(matrix);
	rl.display(matrix);
	rr.display(matrix);
}

void Car::setPosition(glm::vec3& p)
{
	current.position = p;
	box.setPosition(p);

	fl.setPosition(p + glm::vec3(-1.45f, -0.5f, 0.85f));
	fr.setPosition(p + glm::vec3(-1.45f, -0.5f, -0.85f));
	rl.setPosition(p + glm::vec3(1.7f, -0.5f, 0.85f));
	rr.setPosition(p + glm::vec3(1.7f, -0.5f, -0.85f));
}

void Car::setMass(float m)
{
	current.mass = m;
	current.invMass = 1 / m;
	
	box.setMass(m);
	fl.setMass(3.0f);
	fr.setMass(3.0f);
	rl.setMass(3.0f);
	rr.setMass(3.0f);

	fl.setStaticFriction(0.9f);
	fl.setDynamicFriction(0.9f);
	fr.setStaticFriction(0.9f);
	fr.setDynamicFriction(0.9f);
	rl.setStaticFriction(0.9f);
	rl.setDynamicFriction(0.9f);
	rr.setStaticFriction(0.9f);
	rr.setDynamicFriction(0.9f);
}

void Car::setInertia(float i)
{
	current.inertia = glm::mat3(i);
	current.invInertia = glm::inverse(current.inertia);

	box.setInertia(i);
	fl.setInertia(1.0f);
	fr.setInertia(1.0f);
	rl.setInertia(1.0f);
	rr.setInertia(1.0f);
}

void Car::setRestitution(float r)
{
	restitution = r;
	box.setRestitution(r);
	fl.setRestitution(0.8f);
	fr.setRestitution(0.8f);
	rl.setRestitution(0.8f);
	rr.setRestitution(0.8f);
}