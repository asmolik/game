
#pragma once

#include <glm/vec3.hpp>

class DirectionalLight
{
	glm::vec3 color;
	glm::vec3 direction;

public:
	DirectionalLight();
	DirectionalLight(glm::vec3& color, glm::vec3& direction);

	glm::vec3 getColor();
	glm::vec3 getDirection();

	void set(glm::vec3& color, glm::vec3& direction);
};