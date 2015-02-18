#pragma once
#include <glm/glm.hpp>
#include "Physics.h"

class Sun
{
protected:
	glm::vec3 direction;
	glm::vec3 color;
	glm::vec3 ambientLight;
	double sunrise;
	double noon;
	double sunset;

public:
	Sun();
	~Sun();
	glm::vec3& getSunDirection(double hour);
	glm::vec3& getSunColor(double hour);
	glm::vec3& getAmbientLight(double hour);
	void get(double hour, glm::vec3& direction, glm::vec3& color, glm::vec3& ambient);
};
