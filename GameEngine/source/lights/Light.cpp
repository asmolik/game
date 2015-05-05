
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

void Light::setPosition(glm::vec3& p)
{
	position = p;
}
void Light::setColor(glm::vec3& c)
{
	color = c;
}
void Light::set(glm::vec3& c, glm::vec3& p)
{
	color = c;
	position = p;
}