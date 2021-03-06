
#pragma once

#include "Light.h"

class PointLight : public Light
{
	float attenuation;

public:
	PointLight();
	PointLight(glm::vec3& color, glm::vec3& position, float attenuation);

	glm::vec3& getColor();
	glm::vec3& getPosition();
	float getAttenuation();

	void set(glm::vec3& color, glm::vec3& position, float attenuation);
};