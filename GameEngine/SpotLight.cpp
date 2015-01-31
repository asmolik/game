
#include "SpotLight.h"

SpotLight::SpotLight() {}

SpotLight::SpotLight(glm::vec3& c, glm::vec3& p, glm::vec3& d, float at, float an) : 
Light(c, p), direction(d), attenuation(at), angle(an) {}

glm::vec3& SpotLight::getColor()
{
	return color;
}

glm::vec3& SpotLight::getPosition()
{
	return position;
}

glm::vec3& SpotLight::getDirection()
{
	return direction;
}

float SpotLight::getAttenuation()
{
	return attenuation;
}

float SpotLight::getAngle()
{
	return angle;
}

void SpotLight::set(glm::vec3& c, glm::vec3& p, glm::vec3& d, float at, float an)
{
	color = c;
	position = p;
	direction = d;
	attenuation = at;
	angle = an;
}

void SpotLight::display(glm::mat4& camT)
{
	glUniform4fv(lightColor, 1, glm::value_ptr(glm::vec4(color, 0.0f)));
	glUniform4fv(lightPosition, 1, glm::value_ptr(camT * glm::vec4(position, 1.0f)));
	glUniform4fv(lightDirection, 1, glm::value_ptr(camT * glm::vec4(direction, 0.0f)));
	glUniform1f(attenuationUnif, attenuation);
	glUniform1f(angleUnif, std::cosf(angle));
}

void SpotLight::init(GLuint program)
{
	glUseProgram(program);
	lightColor = glGetUniformLocation(program, "lightColor");
	lightPosition = glGetUniformLocation(program, "lightPosition");
	lightDirection = glGetUniformLocation(program, "lightDirection");
	attenuationUnif = glGetUniformLocation(program, "attenuation");
	angleUnif = glGetUniformLocation(program, "spotAngle");
	glUseProgram(0);
}

GLuint SpotLight::lightColor = 0;
GLuint SpotLight::lightPosition = 0;
GLuint SpotLight::lightDirection = 0;
GLuint SpotLight::attenuationUnif = 0;
GLuint SpotLight::angleUnif = 0;