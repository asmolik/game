
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera
{
private:
	glm::vec3 position;
	glm::fquat orientation;
	glm::vec3 force;
	glm::vec3 velocity;

public:
	Camera();
	Camera(glm::vec3 position, glm::fquat orientation);

	glm::mat4 cameraTransform();
	glm::vec3 getPosition();
	glm::fquat getOrientation();

	glm::vec3 getFrontVector();
	glm::vec3 getRightVector();
	glm::vec3 getUpVector();

	void move(glm::vec3& vec);
	void rotate(glm::vec3& axis, float angleDeg);

	void move(float dt);

	void setPosition(glm::vec3& position);
	void setOrientation(glm::fquat& orientation);
	void setVelocity(glm::vec3& velocity);
};

#endif