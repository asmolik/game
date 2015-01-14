
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

	float engineTorque;
	//Position of the throttle [0; 1]
	float throttle;
	//Position of the brake pedal [0; 1]
	float brakePedal;
	float wheelBase;
	float wheelRadius;

	Box box;
	//0 - FL, 1 - FR, 2 - RL, 3 - RR
	std::vector<Wheel> wheels;

public:
	Car();
	/*Car(glm::vec3& position, glm::vec3& normal, float mass, float inertia, float density,
		float restitution, float staticFriction, float dynamicFriction);*/

	void update(float time);

	void integrateForces(float time);

	//Parameters heve to be in range [0; 1]
	void accelerate(float a = 1.0f);
	void brakes(float b = 1.0f);
	void turnLeft(float t = 1.0f);
	void turnRight(float t = 1.0f);

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	void setPosition(glm::vec3& p);

	void setMass(float m);

	void setInertia(float i);

	void setRestitution(float r);

	void accumulateLinearImpulse(glm::vec3& impulse, int wheel);

	//Calculates load on each wheel
	void weightTransfer(float wheelLoad[4]);

	//Calculates slip ratio for each wheel
	void tyreSlip(float slip[4]);

	//Calculates longitudinal force for each wheel
	void longWheelForce(float force[4], float load[4]);

	void driveForce(float force[4], float engineForce);

	void applyLongForces(float force[4]);

private:
	void clearInput();
};

#endif