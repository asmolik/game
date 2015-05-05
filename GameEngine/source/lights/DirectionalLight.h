
#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(glm::vec3& color, glm::vec3& direction);

	glm::vec3 getColor();
	glm::vec3 getDirection();

	void set(glm::vec3& color, glm::vec3& direction);
};