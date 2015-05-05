
#pragma once

#include "Light.h"

class SpotLight : public Light
{
	glm::vec3 direction;
	float attenuation;
	float angle;

	static GLuint lightColor;
	static GLuint lightPosition;
	static GLuint lightDirection;
	static GLuint attenuationUnif;
	static GLuint angleUnif;

public:
	SpotLight();
	SpotLight(glm::vec3& color, glm::vec3& position, glm::vec3& direction, float attenuation, float angle);

	glm::vec3& getColor();
	glm::vec3& getPosition();
	glm::vec3& getDirection();
	float getAttenuation();
	float getAngle();

	void set(glm::vec3& color, glm::vec3& position, glm::vec3& direction, float attenuation, float angle);

	void display(glm::mat4& cameraTransform);
	static void init(GLuint program);
};