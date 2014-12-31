
#include "Car.h"

Car::Car() : RigidBody(3) {}

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
	rl.applyTorque(rl.getRightVector());
	rr.applyTorque(rr.getRightVector());
}

void Car::breaks()
{
	fl.applyTorque(-fl.getRightVector());
	fr.applyTorque(-fr.getRightVector());
	rl.applyTorque(-rl.getRightVector());
	rr.applyTorque(-rr.getRightVector());
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

Contact Car::generateContact(RigidBody& body)
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

	fl.setPosition(p + glm::vec3(-1.45f, -0.5f, 0.7f));
	fr.setPosition(p + glm::vec3(-1.45f, -0.5f, -1.0f));
	rl.setPosition(p + glm::vec3(1.7f, -0.5f, 0.7f));
	rr.setPosition(p + glm::vec3(1.7f, -0.5f, -1.0f));
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
}

void Car::setInertia(float i)
{
	current.inertia = i;
	current.invInertia = 1 / i;

	box.setInertia(i);
	fl.setInertia(3.0f);
	fr.setInertia(3.0f);
	rl.setInertia(3.0f);
	rr.setInertia(3.0f);
}