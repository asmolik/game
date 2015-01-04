
#include "Camera.h"

Camera::Camera(): follow(0) {}

Camera::Camera(glm::vec3 pos, glm::fquat or) : position(pos), orientation(or) {}

glm::mat4 Camera::cameraTransform()
{
	if (follow)
	{
		orientation = follow->getOrientation();
		rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
		position = follow->getPosition() + glm::vec3(-5.0f, 3.0f, 0.0f);
	}
	glm::mat4 mat = glm::mat4_cast(orientation);
	mat = glm::translate(mat, -position);
	return mat;
}

glm::vec3 Camera::getPosition()
{
	return position;
}

glm::vec3 Camera::getFrontVector()
{
	return glm::vec3(0.0, 0.0, -1.0) * orientation;
}

glm::vec3 Camera::getRightVector()
{
	return glm::vec3(1.0, 0.0, 0.0) * orientation;
}

glm::vec3 Camera::getUpVector()
{
	return glm::vec3(0.0, 1.0, 0.0) * orientation;
}

void Camera::move(glm::vec3& v)
{
	position += v;
}

void Camera::rotate(glm::vec3& axis, float angleDeg)
{
	float angleRad = angleDeg * 3.1415926f / 180.0f;

	glm::vec3 a = glm::normalize(axis);

	a = a * sinf(angleRad / 2.0f);
	float scalar = cosf(angleRad / 2.0f);

	glm::fquat offset(scalar, a.x, a.y, a.z);

	orientation = orientation * offset; //world space
	//orientation = offset * orientation; //model space

	orientation = glm::normalize(orientation);
}

void Camera::move(float time)
{
	position += velocity * time;
}

void Camera::setPosition(glm::vec3& pos)
{
	position = pos;
}

void Camera::setOrientation(glm::fquat& ori)
{
	orientation = ori;
}

void Camera::setVelocity(glm::vec3& vel)
{
	velocity = vel;
}

void Camera::setObjectToFollow(RigidBody* object)
{
	follow = object;
}










/*
Camera control

//rotation in world space

int width, height;
glfwGetWindowSize(window, &width, &height);

r->rotateCamera(glm::vec3(0.0f, 1.0f, 0.0f), ((xpos - r->getMouseX()) / 10));
r->rotateCamera(-r->getCameraRightVector(), ((ypos - r->getMouseY()) / 10));

r->setMouseX(xpos);
r->setMouseY(ypos);
xpos = ypos = 0;

- - - - - - - - - - - - - - - - - - - - - - - -

//rotation in model space

int width, height;
glfwGetWindowSize(window, &width, &height);

r->rotateCamera(glm::vec3(0.0f, 1.0f, 0.0f), ((xpos - r->getMouseX()) / 10));
r->rotateCamera(glm::vec3(1.0f, 0.0f, 0.0f), ((ypos - r->getMouseY()) / 10));

r->setMouseX(xpos);
r->setMouseY(ypos);

- - - - - - - - - - - - - - - - - - - - - - - -

//for moving in space

if (action == GLFW_PRESS)
{
switch (key)
{
case GLFW_KEY_W: r->setCameraVelocity(r->getCameraFrontVector() / 0.01f); break;
case GLFW_KEY_S: r->setCameraVelocity(-r->getCameraFrontVector() / 0.01f); break;

case GLFW_KEY_A: r->setCameraVelocity(-r->getCameraRightVector() / 0.01f); break;
case GLFW_KEY_D: r->setCameraVelocity(r->getCameraRightVector() / 0.01f); break;

case GLFW_KEY_Q: r->rotateCamera(glm::vec3(0.0f, 0.0f, 1.0f), 5.0f); break;
case GLFW_KEY_E: r->rotateCamera(glm::vec3(0.0f, 0.0f, 1.0f), -5.0f); break;

case GLFW_KEY_SPACE: r->setCameraVelocity(glm::vec3(0.0f, 10.0f, 0.0f)); break;
}
}
else if (action == GLFW_RELEASE)
{
r->setCameraVelocity(glm::vec3(0.0));
}
- - - - - - - - - - - - - - - - - - - - - - - -

*/