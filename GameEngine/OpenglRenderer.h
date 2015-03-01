#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glutil/glutil.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenglPrograms.h"
#include "GBuffer.h"
#include "UniformBuffer.h"
#include "RigidBody.h"
#include "Object.h"
#include "Mesh.h"
#include "Plane.h"
#include "Track.h"
#include "Box.h"
#include "Wheel.h"
#include "Car.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Quad.h"
#include "Sphere.h"
#include "Cone.h"

class GameEngine;


// Drawing on screen with opengl.
class OpenglRenderer
{
protected:
	GLFWwindow* window;
	int wWidth, wHeight;

	GBuffer gbuffer;
	UniformBuffer* perspectiveMatrixUB;

	std::vector<RigidBody*>* objects;
	Camera* camera;
	std::vector<PointLight>* pointLights;
	std::vector<SpotLight>* spotLights;

	glm::vec3 ambientColor;
	glm::vec3 sunDirection;
	glm::vec3 sunColor;

	glm::mat4 perspectiveMatrix;
	float fFrustumScale;
	float zNear, zFar;

	void init();

public:
	OpenglRenderer(int width, int height, std::string name, void* ptr);
	~OpenglRenderer();

	GLFWwindow* createWindow(int width, int height, std::string name);
	GLFWwindow* getWindow();

	void reshapeWindow(int width, int height);

	void setWindowSize(int width, int height);


	void setWindowUserPointer(void* pointer);
	void setErrorCallback(void* callback);
	void setCursorPosCallback(void* callback);
	void setKeyCallback(void* callback);
	void setWindowSizeCallback(void* callback);

	void setAmbientColor(glm::vec3& color);
	void setSun(glm::vec3& direction, glm::vec3& color);

	// Set the vector of objects to be displayed.
	void setObjects(std::vector<RigidBody*>* objects);
	// Set the camera with which to display the scene.
	void setCamera(Camera* camera);
	// Set the vector of point lights to be displayed.
	void setPointLights(std::vector<PointLight>* pointLights);
	// Set the vector of spotlights to be displayed.
	void setSpotLights(std::vector<SpotLight>* spotLights);

	// Display objects using forward shading.
	void display();

	// Initialize deferred shading.
	// 1. Initialize gbuffer.
	void initializeDS();

	// Display objects and lights using deferred shading.
	void dsDisplay();

	// @return 0 if the window should close.
	int isRunning();

protected:
	// Deferred shading geometry pass.
	void dsGeometry();
	// Deferred shading lighting pass.
	void dsLighting();
	// Deferred shading lighting pass for lights which are connected to rigid bodies.
	void dsLightingFromObjects();
	// Directional light part.
	void dsLightingDirectional();
	// Point light part.
	void dsLightingPoint();
	// Spotlight part.
	void dsLightingSpot();

	// Initialize OpenglPrograms.
	void initializePrograms();
};
