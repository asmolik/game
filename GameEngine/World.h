#pragma once
#include "pugixml.hpp"
#include <string>
#include <cctype>
#include <algorithm>
#include "RigidBody.h"
#include "Object.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"

// Class for managing objects in the game. Provides functions for loading the data from xml
// files by pugixml.
class World
{
	friend class OpenglRenderer;
	friend class GameEngine;
protected:
	std::vector<RigidBody*> objects;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;

public:
	World();
	~World();
	// Load world information from file.
	void loadWorld(const std::string& fileName);

	void addObject(RigidBody& object);
	void addPointLight(PointLight& light);
	void addSpotLight(SpotLight& light);
protected:
	// Load a node of type Object.
	// Check if we recognize the object's subtype. Create a specific object if that's the case.
	// Otherwise signal unknown subtype and try to load it as Object.
	// This signal is a simple console message.
	void loadObject(pugi::xml_node& node);
	// Load a node of type Light.
	// Check if we recognize the light's subtype. Create a specific light if that's the case.
	// Otherwise signal unknown subtype and try to load it as Light.
	// This signal is a simple console message.
	void loadLight(pugi::xml_node& node);
	// Load a material from a file.
	void loadMaterial(const std::string& fileName);
	void loadPointLight(pugi::xml_node& node);
	void removeWihteSpace(std::string& str);
};

