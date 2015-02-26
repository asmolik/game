#pragma once
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <fstream>

namespace MeshImporter
{
	class Material
	{
	protected:
		glm::vec4 diffuseColor;
		glm::vec4 specularColor;
		float shininess;
		std::string diffuseTexture;
		std::string specularTexture;
		std::string shininessTexture;
		std::string normalTexture;

	public:
		Material();
		~Material();

		// Print this material to the specified stream.
		void saveMaterial(std::ostream& os);

		void setDiffuseColor(glm::vec3& color);
		void setDiffuseTexture(std::string& texture);
		void setSpecularColor(glm::vec3& color);
		void setSpecularTexture(std::string& texture);
		void setShininess(float shininess);
		void setShininessTexture(std::string& texture);
		void setNormalTexture(std::string& texture);
	};
}

