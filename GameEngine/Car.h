
#ifndef CAR_H
#define CAR_H

#include "RigidBody.h"
#include "Box.h"
#include "Wheel.h"
#include "Track.h"
#include "Contact.h"

class Car : public RigidBody
{
	friend class GameEngine;
private:
	glm::vec3 massCenter;
	//Impulse generated during one time step with only gravity.
	float normalImpulse;

	float wheelBase;

	Box box;
	std::vector<Wheel> wheels;

public:
	Car();
	/*Car(glm::vec3& position, glm::vec3& normal, float mass, float inertia, float density,
		float restitution, float staticFriction, float dynamicFriction);*/

	void update(float time);

	void accelerate();
	void breaks();
	void turnLeft();
	void turnRight();

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	void setPosition(glm::vec3& p);

	void setMass(float m);

	void setInertia(float i);

	void setRestitution(float r);

	void accumulateLinearImpulse(glm::vec3& impulse, int wheel);
};

#endif