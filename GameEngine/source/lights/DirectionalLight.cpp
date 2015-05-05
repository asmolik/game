
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(glm::vec3& c, glm::vec3& d) : Light(c, d) {}

glm::vec3 DirectionalLight::getColor()
{
	return color;
}

glm::vec3 DirectionalLight::getDirection()
{
	return position;
}

void DirectionalLight::set(glm::vec3& c, glm::vec3& d)
{
	color = c;
	position = d;
}