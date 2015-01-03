
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

	glm::mat3 inertia;
	glm::mat3 invInertia;

	void recalculate();
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
	static const float epsilon;

	/* Evaluate derivative at time t */
	static Derivative evaluate(State& state, float t);

	/* Evaluate derivative at time t + dt using specified derivative */
	static Derivative evaluate(State state, float t, float dt, Derivative& derivative);

	/* Integrate state forward by dt seconds */
	static void integrateRK4(State& state, float t, float dt);

	/* Integrate state forward by dt seconds */
	static void integrate(State& state, float t, float dt);

	static void forces(State& state, float t, glm::vec3& force, glm::vec3& torque);
};

#endif