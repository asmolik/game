#include "Material.h"
using namespace MeshImporter;


Material::Material()
{
}


Material::~Material()
{
}


void Material::setDiffuseColor(glm::vec3& color)
{
	diffuseColor = glm::vec4(color, 1.0f);
}


void Material::setDiffuseTexture(std::string& texture)
{
	diffuseTexture = texture;
}


void Material::setSpecularColor(glm::vec3& color)
{
	specularColor = glm::vec4(color, 1.0f);
}


void Material::setSpecularTexture(std::string& texture)
{
	specularTexture = texture;
}


void Material::setShininess(float s)
{
	shininess = s;
}


void Material::setShininessTexture(std::string& texture)
{
	shininessTexture = texture;
}


void Material::setNormalTexture(std::string& texture)
{
	normalTexture = texture;
}

