#include "World.h"


World::World()
{
}


World::~World()
{
}


// Load world information from file using pugixml.
void World::loadWorld(const std::string& fileName)
{
	pugi::xml_document xml;
	pugi::xml_parse_result result = xml.load_file(fileName.c_str());
	if (!result)
		return;
	for (pugi::xml_node node : xml.child("World"))
	{
		// Check if we recognize the type. If yes, then call appropriate function for loading it.
		std::string type = node.child("Type").text().get();
		removeWihteSpace(type);
		std::cout << node.child("Type").text().get();
		if (type == "Object")
			loadObject(node);
		else if (type == "Light")
			loadLight(node);
	}
}


void World::addObject(RigidBody& object)
{
	objects.push_back(&object);
}


void World::addPointLight(PointLight& light)
{
	pointLights.push_back(light);
}


void World::addSpotLight(SpotLight& light)
{
	spotLights.push_back(light);
}


// Load a node of type Object.
// Check if we recognize the object's subtype. Create a specific object if that's the case.
// Otherwise signal unknown subtype and try to load it as Object.
// This signal is a simple console message.
void World::loadObject(pugi::xml_node& node)
{
	std::string subtype = node.child("Type").child("Subtype").text().get();
	removeWihteSpace(subtype);
	if (subtype == "Car")
		return;
	// Unknown subtype
	else
	{
		std::cout << "Unknown type of object." << std::endl;
		RigidBody* object = new Object();
		// Read the position, rotation and scale.
		glm::vec3 position, scale;
		glm::quat orientation;
		position.x = node.child("Position").child("X").text().as_float();
		position.y = node.child("Position").child("Y").text().as_float();
		position.z = node.child("Position").child("Z").text().as_float();
		orientation.x = node.child("Orientation").child("X").text().as_float();
		orientation.y = node.child("Orientation").child("Y").text().as_float();
		orientation.z = node.child("Orientation").child("Z").text().as_float();
		orientation.w = node.child("Orientation").child("W").text().as_float(1.0f);
		orientation = glm::normalize(orientation);
		scale.x = node.child("Scale").child("X").text().as_float(1.0f);
		scale.y = node.child("Scale").child("Y").text().as_float(1.0f);
		scale.z = node.child("Scale").child("Z").text().as_float(1.0f);
		// Read the mesh.
		std::string meshFile = node.child("Mesh").text().get();
		if (meshFile.length() > 0)
			((Object*)object)->loadMesh(meshFile);
		// Read the material.
		/*std::string materialFile = node.child("Material").text().get();
		if (materialFile.length() > 0)
			((Object*)object)->loadMaterial(materialFile);*/
		objects.push_back(object);
	}
}


// Load a node of type Light.
// Check if we recognize the light's subtype. Create a specific light if that's the case.
// Otherwise signal unknown subtype and try to load it as Light.
// This signal is a simple console message.
void World::loadLight(pugi::xml_node& node)
{
	// Unknown subtype
	std::cout << "Unknown type of light." << std::endl;
	loadPointLight(node);
}


// Load a material from a file.
void World::loadMaterial(const std::string& fileName)
{
}


void World::loadPointLight(pugi::xml_node& node)
{
	PointLight light;
	//Read the position.
	glm::vec3 position, color;
	float attenuation, intensity;
	position.x = node.child("Position").child("X").text().as_float();
	position.y = node.child("Position").child("Y").text().as_float();
	position.z = node.child("Position").child("Z").text().as_float();
	
	// Open properties file and read them.
	std::string propertiesFile = node.child("Properties").text().get();
	removeWihteSpace(propertiesFile);
	pugi::xml_document xml;
	pugi::xml_parse_result result = xml.load_file(propertiesFile.c_str());
	if (!result)
		return;

	// Read the color, intensity and attenuation.
	pugi::xml_node properties = xml.child("Properties");
	color.r = properties.child("Color").child("R").text().as_float();
	color.g = properties.child("Color").child("G").text().as_float();
	color.b = properties.child("Color").child("B").text().as_float();
	intensity = properties.child("Intensity").text().as_float(1.0f);
	color *= intensity;
	attenuation = properties.child("Attenuation").text().as_float();
	light.set(color, position, attenuation);

	pointLights.push_back(light);
}


void World::removeWihteSpace(std::string& str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\f'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\v'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
}
