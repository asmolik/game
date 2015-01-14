
#include "Car.h"

Car::Car() : RigidBody(ObjectIDs::carID), wheelBase(0), throttle(0.0f), brakePedal(0.0f), engineTorque(500.0f), wheelRadius(0.4f)
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
	weightTransfer(wh);

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
	float engineForce = engineTorque * throttle * 10.0f / wheelRadius;
	float brakeForce = -brakePedal * 3000.0f * 4.0f;
	float drag = 0.5f;
	float rollingResistance = 10.0f;
	//calculate forces on car
	current.force += -drag * current.velocity * glm::length(current.velocity);
	current.force += -rollingResistance * current.velocity;

	//weight transfer for each wheel
	float wh[4];
	weightTransfer(wh);

	//calculate longitudinal forces for each wheel
	float force[4];
	longWheelForce(force, wh);

	driveForce(force, engineForce + brakeForce);

	applyLongForces(force);

	//do what every rigidbody
	Physics::integrateForcesSIE(current, time);

	//clear user input before next frame
	clearInput();
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
	wheels[0].rotate(wheels[0].getRightVector(), 60.0f * t);
	wheels[1].rotate(wheels[1].getRightVector(), 60.0f * t);
}

void Car::turnRight(float t)
{
	wheels[0].rotate(wheels[0].getRightVector(), -60.0f * t);
	wheels[1].rotate(wheels[1].getRightVector(), -60.0f * t);
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
				  wheelPos.y -= 0.5;
				  wheelPos = wheelPos * glm::conjugate(current.orientation);
				  //calculate velocity for the wheel
				  glm::vec3 wheelVel = current.velocity + glm::cross(current.angularVelocity, wheelPos);
				  wheelPos += current.position;

				  Track* plane = (Track*)body;
				  if (glm::length(wheelVel) < Physics::epsilon)
					  break;
				  float d = glm::dot(current.velocity, plane->getNormal());
				  glm::vec3 elo = plane->getNormal() * d;
				  float dot = glm::dot(glm::normalize(elo), plane->getNormal());

				  //wheel moves parallel to plane
				  if (dot < Physics::epsilon && dot > -Physics::epsilon /*&& current.position.y > 0.5f*/)
					  break;

				  distance = glm::dot(plane->getNormal(), plane->getPosition() - wheelPos) / dot;
				  toi = distance / glm::length(wheelVel);

				  if (distance < -0.1f)
					  break;

				  glm::vec3 tangent = -wheelVel - (-plane->getNormal() * glm::dot(-wheelVel, -plane->getNormal()));
				  if (glm::length(tangent) < Physics::epsilon)
					  tangent = glm::vec3(0.0f);
				  else
					tangent = glm::normalize(tangent);
				  
				  out = new Contact();
				  out->set(this, body, -plane->getNormal(), tangent, w.getPosition(), glm::vec3(0.0f), distance, toi);
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
	matrix *= glm::mat4_cast(current.orientation);

	box.display(matrix);

	for (Wheel& w : wheels)
	{
		w.display(matrix);
	}
}

void Car::setPosition(glm::vec3& p)
{
	current.position = p;

	wheels[0].setPosition(glm::vec3(1.45f, -0.5f, 0.85f));
	wheels[1].setPosition(glm::vec3(1.45f, -0.5f, -0.85f));
	wheels[2].setPosition(glm::vec3(-1.7f, -0.5f, 0.85f));
	wheels[3].setPosition(glm::vec3(-1.7f, -0.5f, -0.85f));

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

void Car::weightTransfer(float wheel[4])
{
	float weight = current.mass * glm::length(Physics::gravity);
	//front wheels
	for (int i = 0; i < 2; ++i)
	{
		wheel[i] = std::fabs(wheels[0].getPosition().x - massCenter.x) / wheelBase * weight;
		wheel[i] -= massCenter.y / wheelBase * glm::length(current.force) / current.mass;
		wheel[i] /= 2.0f;
	}
	//rear wheels
	for (int i = 2; i < 4; ++i)
	{
		wheel[i] = std::fabs(wheels[0].getPosition().x - massCenter.x) / wheelBase * weight;
		wheel[i] += massCenter.y / wheelBase * glm::length(current.force) / current.mass;
		wheel[i] /= 2.0f;
	}

	//calculate forces on wheels from collision detection	@TODO
	float d = 0.0f;
	for (Wheel& w : wheels)
		d += glm::length(w.getLinearImpulse());
}

void Car::tyreSlip(float slip[4])
{
	float C = 2.0f;
	for (int i = 0; i < 4; i++)
	{
		slip[i] = 0.0f;
		if (glm::length(wheels[i].getAngularVelocity()) > Physics::epsilon)
			slip[i] = glm::length(wheels[i].getAngularVelocity()) * wheelRadius;
		//longitudinal velocity
		float longVel = glm::dot(current.velocity, getFrontVector());
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
		glm::vec3 wheelPos = wheels[i].getPosition();
		wheelPos.y -= 0.5;
		wheelPos = wheelPos * glm::conjugate(current.orientation);
		
		glm::vec3 linearForce = force[i] * wheels[i].getFrontVector();
		applyForce(linearForce);
		//applyTorque(glm::cross(-linearForce / 100.0f, wheelPos));
	}
}

void Car::longWheelForce(float force[4], float load[4])
{
	tyreSlip(force);
	for (int i = 0; i < 4; ++i)
	{
		force[i] *= load[i];
	}
}

void Car::clearInput()
{
	throttle = 0.0f;
	brakePedal = 0.0f;
}