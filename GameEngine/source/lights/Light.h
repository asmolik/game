
#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glutil/MatrixStack.h>

class Light
{
protected:
	glm::vec3 color;
	glm::vec3 position;

public:
	Light();
	Light(glm::vec3& color, glm::vec3& position);

	glm::vec3& getColor();
	glm::vec3& getPosition();

	void setPosition(glm::vec3& position);
	void setColor(glm::vec3& color);
	virtual void set(glm::vec3& color, glm::vec3& position);

	//virtual void display(glutil::MatrixStack& matrix) = 0;
};