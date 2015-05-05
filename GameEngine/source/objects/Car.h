
#ifndef CAR_H
#define CAR_H

#include "RigidBody.h"
#include "Box.h"
#include "Wheel.h"
#include "Track.h"
#include "Contact.h"
#include "SpotLight.h"
#include "Cone.h"

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
	//Rotation of the front wheels [-1; 1]
	float frontWheelRot;
	float maxFrontWheelRot;
	float wheelBase;
	//distance between left and right wheel
	float trackWidth;
	float wheelRadius;

	Box box;
	//0 - FL, 1 - FR, 2 - RL, 3 - RR
	std::vector<Wheel> wheels;
	std::vector<SpotLight> lights;

public:
	Car();
	/*Car(glm::vec3& position, glm::vec3& normal, float mass, float inertia, float density,
		float restitution, float staticFriction, float dynamicFriction);*/

	void update(float time);

	void integrateForces(float time);
	void integrateVelocities(float time);

	//Parameters heve to be in range [0; 1]
	void accelerate(float a = 1.0f);
	void brakes(float b = 1.0f);
	void turnLeft(float t);
	void turnRight(float t);
	void turnLeft();
	void turnRight();

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);
	void displayLights(glutil::MatrixStack &matrix, glm::mat4& cameraTransform);

	void setPosition(glm::vec3& p);

	void setMass(float m);

	void setInertia(float i);

	void setRestitution(float r);

	void accumulateLinearImpulse(glm::vec3& impulse, int wheel);

	//Calculates load on each wheel
	void loadTransfer(float wheelLoad[4]);

	//Calculates slip ratio for each wheel
	void longTyreSlip(float slip[4]);

	//Calculates maximum longitudinal force for each wheel
	void longWheelForce(float force[4], float load[4]);

	//Calculate actual longitudinal force for each wheel
	void driveForce(float force[4], float engineForce);

	void applyLongForces(float force[4]);

	void latTyreSlip(float slip[4]);

	//Calculates lateral force for each wheel
	void latWheelForce(float force[4], float load[4]);

	void applyLatForces(float force[4]);

private:
	void clearInput();
};

#endif