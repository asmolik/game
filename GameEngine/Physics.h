
#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct State
{
	glm::vec3 position;
	glm::vec3 momentum;
	glm::quat orientation;
	glm::vec3 angularMomentum;

	glm::vec3 velocity;
	glm::quat spin;
	glm::vec3 angularVelocity;

	glm::vec3 force;
	glm::vec3 torque;

	float mass;
	float invMass;

	float inertia;
	float invInertia;

	void recalculate()
	{
		velocity = momentum * invMass;
		angularVelocity = angularMomentum * invInertia;
		glm::normalize(orientation);
		spin = 0.5f * glm::quat(0.0f, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
	}
};

struct Derivative
{
	glm::vec3 velocity;
	glm::vec3 force;
	glm::quat spin;
	glm::vec3 torque;
};

class Physics
{
public:

	/* Evaluate derivative at time t */
	static Derivative evaluate(State& state, float t);

	/* Evaluate derivative at time t + dt using specified derivative */
	static Derivative evaluate(State state, float t, float dt, Derivative& derivative);

	/* Integrate state forward by dt seconds */
	static void integrate(State& state, float t, float dt);

	static void forces(State& state, float t, glm::vec3& force, glm::vec3& torque);
};

#endif