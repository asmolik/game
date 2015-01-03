
#ifndef CAR_H
#define CAR_H

#include "RigidBody.h"
#include "Box.h"
#include "Wheel.h"
#include "Contact.h"

class Car : public RigidBody
{
	friend class GameEngine;
private:
	Box box;
	Wheel fl, fr, rl, rr;

public:
	Car();
	/*Car(glm::vec3& position, glm::vec3& normal, float mass, float inertia, float density,
		float restitution, float staticFriction, float dynamicFriction);*/

	void update(float timeStep);

	void accelerate();
	void breaks();
	void turnLeft();
	void turnRight();

	Contact generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	void setPosition(glm::vec3& p);

	void setMass(float m);

	void setInertia(float i);

	void setRestitution(float r);
};

#endif