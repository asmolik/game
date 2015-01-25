
#include "Car.h"

Car::Car() : RigidBody(ObjectIDs::carID), wheelBase(0), throttle(0.0f), brakePedal(0.0f), engineTorque(500.0f), 
wheelRadius(0.4f), frontWheelRot(0.0f), trackWidth(2.0f), maxFrontWheelRot(Physics::pi / 3.0f)
{
	massCenter = glm::vec3(0.0f, 0.2f, 0.0f);

	box.setSize(glm::vec3(4.5f, 1.5f, 2.0f));
	Wheel fl, fr, rl, rr;
	wheels.push_back(fl);
	wheels.push_back(fr);
	wheels.push_back(rl);
	wheels.push_back(rr);
}

/*Car::Car(glm::vec3& p, glm::vec3& n, float m, float i = 0, float d = 0,
	float r = 0, float sf = 0, float df = 0) : RigidBody(0, p, glm::vec3(), m, i, d, r, sf, df) {}*/

void Car::update(float time)
{
	float engineForce = engineTorque * 10.0f / wheelRadius;
	float drag = 0.5f;
	float rollingResistance = 10.0f;
	//calculate forces on car
	current.force += getFrontVector() * engineForce * throttle; //this line should be after weight transfer and take it into account
	current.force += -drag * current.velocity * glm::length(current.velocity);
	current.force += -rollingResistance * current.velocity;

	//weight transfer for each wheel
	float wh[4];
	loadTransfer(wh);

	//calculate longitudinal forces for each wheel
	float force[4];
	longWheelForce(force, wh);

	applyLongForces(force);

	previous = current;
	Physics::integrateSIE(current, 0, time);
	current.accumulatedLinearImpulse = glm::vec3(0.0f);
	current.accumulatedAngularImpulse = glm::vec3(0.0f);
	for (Wheel& w : wheels)
		w.clearAccumulatedImpulses();
	//clear user input before next frame
	clearInput();
}

void Car::integrateForces(float time)
{
	glm::vec3 f = getFrontVector();
	glm::vec3 r = getRightVector();
	glm::vec3 u = getUpVector();

	float engineForce = engineTorque * throttle * 10.0f / wheelRadius;
	float brakeForce = -brakePedal * 3000.0f * 4.0f;
	float drag = 0.5f;
	float rollingResistance = 10.0f;
	//calculate forces on car
	current.force += -drag * current.velocity * glm::length(current.velocity);
	current.force += -rollingResistance * current.velocity;

	//weight transfer for each wheel
	float wh[4];
	loadTransfer(wh);

	//calculate longitudinal forces for each wheel
	float force[4];
	longWheelForce(force, wh);
	driveForce(force, engineForce + brakeForce);
	applyLongForces(force);

	//calculate lateral forces for each wheel
	latWheelForce(force, wh);
	applyLatForces(force);

	//do what every rigidbody
	previous = current;
	Physics::integrateForcesSIE(current, time);

	//clear user input before next frame
	clearInput();
}

void Car::integrateVelocities(float time)
{
	Physics::integrateVelocitiesSIE(current, time);
	current.accumulatedLinearImpulse = glm::vec3(0.0f);
	current.accumulatedAngularImpulse = glm::vec3(0.0f);
	box.setOrientation(current.orientation);
}

void Car::accelerate(float a)
{
	throttle = a;
}

void Car::brakes(float b)
{
	brakePedal = b;
}

void Car::turnLeft(float t)
{
	frontWheelRot = -t;
}

void Car::turnRight(float t)
{
	frontWheelRot = t;
}

void Car::turnLeft()
{
	frontWheelRot += -0.15f;
	if (frontWheelRot < -1.0f)
		frontWheelRot = -1.0f;
}

void Car::turnRight()
{
	frontWheelRot += 0.15f;
	if (frontWheelRot > 1.0f)
		frontWheelRot = 1.0f;
}

std::vector<Contact*> Car::generateContact(RigidBody* body)
{
	std::vector<Contact*> contacts;
	Contact* out;
	float distance, toi;

	switch (body->getID())
	{
		//track
	case 4:
	{
			  //Check for contact for each wheel
			  for (Wheel& w : wheels)
			  {
				  glm::vec3 wheelPos = w.getPosition();
				  wheelPos = wheelPos * glm::inverse(current.orientation);
				  glm::vec3 point1 = wheelPos;
				  wheelPos.y -= 0.5;
				  //calculate velocity for the wheel
				  glm::vec3 wheelVel = current.velocity + glm::cross(current.angularVelocity, wheelPos);
				  wheelPos += current.position;

				  Track* plane = (Track*)body;
				  if (glm::length(wheelVel) < Physics::epsilon)
					  break;
				  float d = glm::dot(current.velocity, plane->getNormal());
				  glm::vec3 elo = plane->getNormal() * d;
				  float dot = glm::dot(glm::normalize(elo), plane->getNormal());
				  if (std::fabs(d) < Physics::epsilon)
					  dot = 0.0f;

				  //wheel moves parallel to plane
				  if (dot < Physics::epsilon && dot > -Physics::epsilon /*&& current.position.y > 0.5f*/)
					  break;

				  distance = glm::dot(plane->getNormal(), plane->getPosition() - wheelPos) / dot;
				  toi = distance / glm::length(wheelVel);

				  if (distance < -0.4f)
					  break;

				  glm::vec3 tangent = -wheelVel - (-plane->getNormal() * glm::dot(-wheelVel, -plane->getNormal()));
				  if (glm::length(tangent) < Physics::epsilon)
					  tangent = glm::vec3(0.0f);
				  else
					  tangent = glm::normalize(tangent);

				  out = new Contact();
				  out->set(this, body, -plane->getNormal(), tangent, point1, glm::vec3(0.0f), distance, toi);
				  contacts.push_back(out);
			  }

			  break;
	}
	default:
		break;
	}
	return contacts;
}

void Car::display(glutil::MatrixStack &matrix)
{
	glutil::PushStack push(matrix);

	matrix.Translate(current.position);

	box.display(matrix);

	matrix *= glm::mat4_cast(current.orientation);
	for (Wheel& w : wheels)
	{
		w.display(matrix);
	}
}

void Car::setPosition(glm::vec3& p)
{
	current.position = p;

	wheels[0].setPosition(glm::vec3(1.7f, -0.5f, -0.85f));
	wheels[1].setPosition(glm::vec3(1.7f, -0.5f, 0.85f));
	wheels[2].setPosition(glm::vec3(-1.7f, -0.5f, -0.85f));
	wheels[3].setPosition(glm::vec3(-1.7f, -0.5f, 0.85f));

	wheelBase = 1.7f + 1.45f;
}

void Car::setMass(float m)
{
	current.mass = m;
	current.invMass = 1 / m;
	
	box.setMass(m);
	for (Wheel& w : wheels)
	{
		w.setMass(3.0f);
		w.setStaticFriction(0.9f);
		w.setDynamicFriction(0.9f);
	}

	normalImpulse = 400.0f;
}

void Car::setInertia(float i)
{
	current.inertia = glm::mat3(i);
	current.invInertia = glm::inverse(current.inertia);

	box.setInertia(i);
	for (Wheel& w : wheels)
	{
		w.setInertia(1.0f);
	}
}

void Car::setRestitution(float r)
{
	restitution = r;
	box.setRestitution(r);
	for (Wheel& w : wheels)
	{
		w.setRestitution(0.8f);
	}
}

void Car::accumulateLinearImpulse(glm::vec3& i, int w)
{
	current.accumulatedLinearImpulse += i;
	wheels[w].accumulateLinearImpulse(i);
}

void Car::loadTransfer(float wheel[4])
{
	float weight = current.mass * glm::length(Physics::gravity);
	float frontAcc = (glm::dot(current.velocity, getFrontVector()) - glm::dot(previous.velocity, getFrontVector())) * 60.0f;
	float sideAcc = (glm::dot(current.velocity, getRightVector()) - glm::dot(previous.velocity, getRightVector())) * 60.0f;

	//front left
	//longitudinal
	wheel[0] = std::fabs(wheels[0].getPosition().x - massCenter.x) / wheelBase * weight;
	wheel[0] -= massCenter.y / wheelBase * frontAcc * current.mass;
	wheel[0] /= 2.0f;
	//lateral
	wheel[0] += sideAcc / glm::length(Physics::gravity) * wheel[0] * massCenter.y / trackWidth;

	//front right
	//longitudinal
	wheel[1] = std::fabs(wheels[1].getPosition().x - massCenter.x) / wheelBase * weight;
	wheel[1] -= massCenter.y / wheelBase * frontAcc * current.mass;
	wheel[1] /= 2.0f;
	//lateral
	wheel[1] -= sideAcc / glm::length(Physics::gravity) * wheel[1] * massCenter.y / trackWidth;


	//rear left
	//longitudinal
	wheel[2] = std::fabs(wheels[2].getPosition().x - massCenter.x) / wheelBase * weight;
	wheel[2] += massCenter.y / wheelBase * frontAcc * current.mass;
	wheel[2] /= 2.0f;
	//lateral
	wheel[2] += sideAcc / glm::length(Physics::gravity) * wheel[2] * massCenter.y / trackWidth;


	//rear right
	//longitudinal
	wheel[3] = std::fabs(wheels[3].getPosition().x - massCenter.x) / wheelBase * weight;
	wheel[3] += massCenter.y / wheelBase * frontAcc * current.mass;
	wheel[3] /= 2.0f;
	//lateral
	wheel[3] -= sideAcc / glm::length(Physics::gravity) * wheel[3] * massCenter.y / trackWidth;

	//calculate forces on wheels from collision detection	@TODO
	float d = 0.0f;
	for (Wheel& w : wheels)
		d += glm::length(w.getLinearImpulse());
}

void Car::longTyreSlip(float slip[4])
{
	float C = 2.0f;
	float longVel = glm::dot(current.velocity, getFrontVector());
	for (int i = 0; i < 4; i++)
	{
		slip[i] = 0.0f;
		slip[i] = wheels[i].getAngularVelocity().x * wheelRadius;
		//longitudinal velocity
		slip[i] -= longVel;
		if (std::fabs(longVel) > Physics::epsilon)
			slip[i] /= std::fabs(longVel);
		slip[i] = std::max(slip[i] * C, 1.2f);
	}
}

void Car::driveForce(float force[4], float engineForce)
{
	engineForce /= 2.0f;
	//rear wheel drive
	for (int i = 0; i < 2; ++i)
		force[i] = 0.0f;
	for (int i = 2; i < 4; ++i)
	{
		force[i] = std::min(engineForce, force[i]);
	}
}

void Car::applyLongForces(float force[4])
{
	for (int i = 0; i < 4; ++i)
	{
		glm::vec3 linearForce = force[i] * getFrontVector();
		applyForce(linearForce);
	}
}

void Car::longWheelForce(float force[4], float load[4])
{
	longTyreSlip(force);
	for (int i = 0; i < 4; ++i)
	{
		force[i] *= load[i];
	}
}

void Car::latTyreSlip(float slip[4])
{
	float longVel;
	float latVel;
	glm::vec3 wheelPos;
	glm::vec3 angular;
	for (int i = 0; i < 4; ++i)
	{
		wheelPos = wheels[i].getPosition();
		wheelPos = wheelPos * glm::conjugate(current.orientation);
		longVel = glm::dot(current.velocity, getFrontVector());
		latVel = glm::dot(current.velocity, getRightVector());
		angular = glm::cross(current.angularVelocity, wheelPos);
		latVel += glm::length(angular) * Physics::signum(glm::dot(angular, getRightVector()));
		//slip[i] = -std::atan2f(longVel, latVel);
		if (std::fabs(longVel) > Physics::epsilon)
			slip[i] = -std::atanf(latVel / longVel);
		else
			slip[i] = -std::atanf(latVel);
	}
	slip[0] += frontWheelRot * maxFrontWheelRot;
	slip[1] += frontWheelRot * maxFrontWheelRot;
	/*if (std::fabs(latVel) < 0.1f)
		slip[0] = slip[1] = slip[2] = slip[3] = 0.0f;*/
}

void Car::latWheelForce(float force[4], float load[4])
{
	latTyreSlip(force);

	float radius = wheelBase / std::fabs(std::sinf(frontWheelRot * Physics::pi / 3.0f));
	float longVel = glm::dot(current.velocity, getFrontVector());
	float centripetalForce = current.mass * longVel * longVel / radius;
	if (std::fabs(frontWheelRot) < Physics::epsilon)
		centripetalForce = 0.0f;

	for (int i = 0; i < 4; ++i)
	{
		//force[i] = std::min(force[i] * centripetalForce, load[i]);
		force[i] = force[i] * load[i];
		if (force[i] > 0)
			force[i] = std::min(load[i] * 1.2f, force[i]);
		else
			force[i] = std::max(-load[i] * 1.2f, force[i]);
	}
}

void Car::applyLatForces(float force[4])
{
	//cornering force
	glm::vec3 latForce(0.0f);
	glm::vec3 torque(0.0f);
	float cos = std::cosf(frontWheelRot);

	latForce += force[0] * getRightVector() * cos;
	latForce += force[1] * getRightVector() * cos;
	latForce += force[2] * getRightVector();
	latForce += force[3] * getRightVector();

	torque = -getUpVector() * 
		(cos * (force[0] + force[1]) * std::fabs(wheels[0].getPosition().x - massCenter.x) - 
		(force[2] + force[3]) * std::fabs(wheels[2].getPosition().x - massCenter.x));

	applyForce(latForce);
	applyTorque(torque);
}

void Car::clearInput()
{
	throttle = 0.0f;
	brakePedal = 0.0f;
	/*if (frontWheelRot > 0)
		frontWheelRot -= 0.01f;
	if (frontWheelRot < 0)
		frontWheelRot += 0.01f;*/
	frontWheelRot = 0.0f;
}