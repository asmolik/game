
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

class Contact;

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <glutil/glutil.h>
#include <SOIL.h>
#include <vector>
#include "ObjectIDs.h"
#include "Physics.h"

class RigidBody
{
protected:
	int rigidBodyID;
	State previous, current;

	float density;
	float restitution;

	float staticFriction;
	float dynamicFriction;

public:
	RigidBody();
	RigidBody(int id);

	virtual std::vector<Contact*> generateContact(RigidBody* body) = 0;

	/* Updates physics state. */
	virtual void update(float time);

	virtual void integrateForces(float time);
	virtual void integrateVelocities(float time);

	/* Adds force f to body's current force vector. */
	void applyForce(glm::vec3& f);

	/* Adds torque f to body's current torque vector. */
	void applyTorque(glm::vec3& f);

	void applyLinearImpulse(glm::vec3& i);
	void applyAngularImpulse(glm::vec3& i);

	void applyMomentum(glm::vec3& m);

	void applyAngularMomentum(glm::vec3& m);


	/* Draws this body (opengl). */
	virtual void display(glutil::MatrixStack &matrix) = 0;


	glm::vec3 getFrontVector();
	glm::vec3 getRightVector();
	glm::vec3 getUpVector();


	int getID();
	glm::vec3 getPosition();
	glm::vec3 getMomentum();
	glm::vec3 getAngularMomentum();
	glm::vec3 getVelocity();
	glm::vec3 getForce();
	glm::quat getOrientation();
	glm::vec3 getAngularVelocity();

	float getMass();
	float getInvMass();
	
	glm::mat3 getInertia();
	glm::mat3 getInvInertia();

	float getDensity();
	float getRestitution();

	float getStaticFriction();
	float getDynamicFriction();

	void setID(int id);

	void setPosition(glm::vec3& p);
	void setMomentum(glm::vec3& m);
	void setOrientation(glm::quat& o);
	void rotate(glm::vec3& axis, float angleDeg);
	void setAngularMomentum(glm::vec3& m);
	void setVelocity(glm::vec3& v);
	void setSpin(glm::quat& s);
	void setAngularVelocity(glm::vec3& v);

	void setForce(glm::vec3& f);
	void zeroForce();
	void setTorque(glm::vec3& t);
	
	/* Sets mass of the body. If the argument is 0, the body has infinite mass (invMass = 0). */
	void setMass(float m);

	void setInertia(float i);
	void setInertia(glm::mat3& i);

	void setDensity(float d);
	virtual void setRestitution(float r);

	void setStaticFriction(float f);
	void setDynamicFriction(float f);

	void accumulateLinearImpulse(glm::vec3& impusle);
	void accumulateAngularImpulse(glm::vec3& impusle);

	glm::vec3 getLinearImpulse();
	glm::vec3 getAngularImpulse();

	void clearAccumulatedImpulses();
};

#endif