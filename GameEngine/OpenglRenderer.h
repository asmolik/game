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

/*
Drawing on screen with opengl.
*/
class OpenglRenderer
{
private:
	GLFWwindow* window;
	int wWidth, wHeight;
	std::vector<GLuint> programs;

	GBuffer gbuffer;

	float zNear, zFar;

	glm::vec3 ambientColor;
	glm::vec3 sunDirection;
	glm::vec3 sunColor;

	glm::mat4 perspectiveMatrix;
	float fFrustumScale;

	void init();

public:
	OpenglRenderer(int width, int height, std::string name, void* ptr);

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

	/*
	Display objects using forward shading.
	*/
	void display(std::vector<RigidBody*>& objects, Camera& camera);

	/*
	Initialize deferred shading.
	1. Initialize gbuffer.
	*/
	void initializeDS();

	/*
	Display objects and lights using deferred shading.
	*/
	void dsDisplay(std::vector<RigidBody*>& objects, std::vector<PointLight>& pLights, 
		std::vector<SpotLight>& sLights, Camera& camera);

	/* @return 0 if the window should close. */
	int isRunning();

protected:
	/* Deferred shading geometry pass. */
	void dsGeometry(std::vector<RigidBody*>& objects, Camera& camera);
	/* Deferred shading lighting pass. */
	void dsLighting(std::vector<PointLight>& pLights,
		std::vector<SpotLight>& sLights, Camera& camera);
	/* Deferred shading lighting pass for lights which are connected to rigid bodies. */
	void dsLighting(std::vector<RigidBody*>& objects, Camera& camera);
	/* Directional light part. */
	void dsLightingDirectional(Camera& camera);
	/* Point light part. */
	void dsLightingPoint(std::vector<PointLight>& pLights, Camera& camera);
	/* Spot light part. */
	void dsLightingSpot(std::vector<SpotLight>& sLights, Camera& camera);


	std::string txtToString(std::string fileName);

	GLuint createShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint createProgram(const std::vector<GLuint> &shaderList);

	void initializeProgram(std::vector<GLuint> &programs);
	
	/* Initialize opengl program for displaying objects with textures. */
	void initProgramdsPNTxDS();
	/* Initialize opengl program for displaying objects with a uniform material. */
	void initProgramdsPN();
};
