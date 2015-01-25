
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(glm::vec3& c, glm::vec3& d) : color(c), direction(d) {}

glm::vec3 DirectionalLight::getColor()
{
	return color;
}

glm::vec3 DirectionalLight::getDirection()
{
	return direction;
}

void DirectionalLight::set(glm::vec3& c, glm::vec3& d)
{
	color = c;
	direction = d;
}