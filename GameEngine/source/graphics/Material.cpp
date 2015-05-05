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
		glUniform4fv(diffuseUnif, 1, glm::value_ptr(diffuseColor));
	if (specularTexture)
		specularTexture->bind();
	else
		glUniform4fv(specularUnif, 1, glm::value_ptr(specularColor));
}


void Material::setDiffuseColor(glm::vec3& color)
{
	diffuseColor = glm::vec4(color, 1.0f);
}


void Material::setDiffuseTexture(Texture* texture)
{
	diffuseTexture = texture;
}


void Material::setSpecularColor(glm::vec3& color)
{
	specularColor = glm::vec4(color, 1.0f);
}


void Material::setSpecularTexture(Texture* texture)
{
	specularTexture = texture;
}


void Material::setShininess(float s)
{
	shininess = s;
}


void Material::setUniforms(GLuint diffuse, GLuint specular, GLuint shininess)
{
	diffuseUnif = diffuse;
	specularUnif = specular;
	shininessUnif = shininess;
}
