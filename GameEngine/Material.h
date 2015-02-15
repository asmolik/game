
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.h"

class Material
{
protected:
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;
	Texture* diffuseTexture;
	Texture* specularTexture;

	GLuint diffuseUnif;
	GLuint specularUnif;
	GLuint shininessUnif;
public:
	Material();
	~Material();

	void load();

	void setDiffuseColor(glm::vec3& color);
	void setDiffuseTexture(Texture* texture);
	void setSpecularColor(glm::vec3& color);
	void setSpecularTexture(Texture* texture);
	void setShininess(float shininess);
};

