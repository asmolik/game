#include "Material.h"


Material::Material()
{
	shininess = 1.0f;
	diffuseTexture = 0;
	specularTexture = 0;
}


Material::~Material()
{
	delete diffuseTexture;
	delete specularTexture;
}


void Material::load()
{
	glUniform1f(shininessUnif, shininess);
	if (diffuseTexture)
		diffuseTexture->bind();
	else
		glUniform3fv(diffuseUnif, glm::value_ptr(diffuseColor));
	if (specularTexture)
		specularTexture->bind();
	else
		glUniform3fv(specularUnif, glm::value_ptr(specularColor));
}


void Material::setDiffuseColor(glm::vec3& color)
{
	diffuseColor = color;
}


void Material::setDiffuseTexture(Texture* texture)
{
	diffuseTexture = texture;
}


void Material::setSpecularColor(glm::vec3& color)
{
	specularColor = color;
}


void Material::setSpecularTexture(Texture* texture)
{
	specularTexture = texture;
}


void Material::setShininess(float s)
{
	shininess = s;
}
