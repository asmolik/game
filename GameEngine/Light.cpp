
#include "Light.h"

Light::Light() {}

Light::Light(glm::vec3& c, glm::vec3& p) : color(c), position(p) {}

glm::vec3& Light::getColor()
{
	return color;
}

glm::vec3& Light::getPosition()
{
	return position;
}

void Light::set(glm::vec3& c, glm::vec3& p)
{
	color = c;
	position = p;
}