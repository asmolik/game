#include "Sun.h"


Sun::Sun()
{
	sunrise = 4.0;
	sunset = 22.0;
	noon = 12.0;
}


Sun::~Sun()
{
}


glm::vec3& Sun::getSunDirection(double hour)
{
	if (hour < sunrise || hour > sunset)
		direction = glm::vec3(0.0f, 1.0f, 0.0f);
	else
	{
		double t = Physics::pi * hour / 24.0;
		direction = glm::normalize(glm::vec3(std::cosf(t), -std::sinf(t), 0.0f));
	}
	return direction;
}


glm::vec3& Sun::getSunColor(double hour)
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	if (hour > sunrise && hour < sunset)
	{
		float s = std::sinf(hour);
		color *= s * 10000.0f;
	}
	return color;
}


glm::vec3& Sun::getAmbientLight(double hour)
{
	return ambientLight;
}


void Sun::get(double hour, glm::vec3& dir, glm::vec3& col, glm::vec3& ambient)
{
	dir = direction;
	col = color;
	ambient = ambientLight;
}
