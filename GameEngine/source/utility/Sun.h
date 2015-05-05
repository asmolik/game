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
	/*
	@param hour current hour for which the sun direction is calculated.
	*/
	glm::vec3& getSunDirection(double hour);
	/*
	@param hour current hour for which the sun color is calculated.
	*/
	glm::vec3& getSunColor(double hour);
	/*
	@param hour current hour for which the ambient light is calculated.
	*/
	glm::vec3& getAmbientLight(double hour);
	/*
	@param hour current hour for which the global light is calculated.
	*/
	void get(double hour, glm::vec3& direction, glm::vec3& color, glm::vec3& ambient);
};
