#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "RigidBody.h"

class Camera
{
private:
	RigidBody* follow;

	glm::vec3 position;
	glm::fquat orientation;
	glm::vec3 force;
	glm::vec3 velocity;

public:
	Camera();
	Camera(glm::vec3 position, glm::fquat orientation);

	/*
	Get current transformation matrix from world space to camera space.
	*/
	glm::mat4 cameraTransform();
	glm::vec3 getPosition();
	glm::fquat getOrientation();
	RigidBody* getFollowedObject();

	float getX();
	float getY();
	float getZ();

	glm::vec3 getFrontVector();
	glm::vec3 getRightVector();
	glm::vec3 getUpVector();

	void move(glm::vec3& vec);
	void rotate(glm::vec3& axis, float angleDeg);

	void move(float dt);

	void setPosition(glm::vec3& position);
	void setOrientation(glm::fquat& orientation);
	void setVelocity(glm::vec3& velocity);
	void setObjectToFollow(RigidBody* object);
};
