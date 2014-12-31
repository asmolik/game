
#include "Physics.h"

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

void Physics::integrate(State& state, float t, float dt)
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

void Physics::forces(State& state, float t, glm::vec3& force, glm::vec3& torque)
{
	force = state.force;
	torque = state.torque;
}