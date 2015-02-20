
#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"

/*
Material for an object. Consists of diffuse color, specular color and shininess.
Diffuse and specular color can be read from textures.
*/
class Material
{
protected:
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	float shininess;
	Texture* diffuseTexture;
	Texture* specularTexture;

	GLuint diffuseUnif;
	GLuint specularUnif;
	GLuint shininessUnif;
public:
	Material();
	~Material();

	//Loads material information to opengl program.
	void load();

	void setDiffuseColor(glm::vec3& color);
	void setDiffuseTexture(Texture* texture);
	void setSpecularColor(glm::vec3& color);
	void setSpecularTexture(Texture* texture);
	void setShininess(float shininess);
	void setUniforms(GLuint diffuse, GLuint specular, GLuint shininess);
};

