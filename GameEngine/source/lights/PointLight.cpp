
#include "PointLight.h"

PointLight::PointLight() {}

PointLight::PointLight(glm::vec3& c, glm::vec3& p, float a) : Light(c, p), attenuation(a) {}

glm::vec3& PointLight::getColor()
{
	return color;
}

glm::vec3& PointLight::getPosition()
{
	return position;
}

float PointLight::getAttenuation()
{
	return attenuation;
}

void PointLight::set(glm::vec3& c, glm::vec3& p, float a)
{
	color = c;
	position = p;
	attenuation = a;
}