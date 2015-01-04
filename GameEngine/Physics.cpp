
#include "Physics.h"

const float Physics::epsilon = 1.0e-8;

void State::recalculate()
{
	velocity = momentum * invMass;
	angularVelocity = angularMomentum * invInertia;
	glm::normalize(orientation);
	spin = 0.5f * glm::quat(0.0f, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
}

Derivative Physics::evaluate(State& state, float t)
{
	Derivative out;
	out.velocity = state.velocity;
	out.spin = state.spin;
	Physics::forces(state, t, out.force, out.torque);
	return out;
}

Derivative Physics::evaluate(State state, float t, float dt, Derivative& derivative)
{
	state.position += derivative.velocity * dt;
	state.momentum += derivative.force * dt;
	state.orientation += derivative.spin * dt;
	state.angularMomentum += derivative.torque * dt;
	state.recalculate();

	Derivative out;
	out.velocity = state.velocity;
	out.spin = state.spin;
	Physics::forces(state, t + dt, out.force, out.torque);
	return out;
}

void Physics::integrateRK4(State& state, float t, float dt)
{
	Derivative a = evaluate(state, t);
	Derivative b = evaluate(state, t, dt*0.5f, a);
	Derivative c = evaluate(state, t, dt*0.5f, b);
	Derivative d = evaluate(state, t, dt, c);

	state.position += 1.0f / 6.0f * dt * (a.velocity + 2.0f*(b.velocity + c.velocity) + d.velocity);
	state.momentum += 1.0f / 6.0f * dt * (a.force + 2.0f*(b.force + c.force) + d.force);
	state.orientation += 1.0f / 6.0f * dt * (a.spin + 2.0f*(b.spin + c.spin) + d.spin);
	state.angularMomentum += 1.0f / 6.0f * dt * (a.torque + 2.0f*(b.torque + c.torque) + d.torque);

	state.recalculate();
}

void Physics::integrate(State& state, float t, float dt)
{
	state.momentum += state.force * dt;
	state.velocity = state.momentum * state.invMass;
	state.position += state.velocity * dt;

	state.angularMomentum += state.torque * dt;
	state.angularVelocity = state.angularMomentum * state.invInertia;
	state.spin = 0.5f * glm::quat(0.0f, state.angularVelocity.x, state.angularVelocity.y, state.angularVelocity.z) * state.orientation;
	state.orientation += state.spin * dt;
	glm::normalize(state.orientation);
}

void Physics::forces(State& state, float t, glm::vec3& force, glm::vec3& torque)
{
	//add friction force
	force = state.force - state.velocity * 0.1f;
	torque = state.torque - state.angularVelocity * 0.01f;
}