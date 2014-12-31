
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glutil/glutil.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RigidBody.h"
#include "Plane.h"
#include "Track.h"
#include "Box.h"
#include "Wheel.h"
#include "Car.h"
#include "Camera.h"

class GameEngine;

class OpenglRenderer
{
private:
	GLFWwindow* window;
	std::vector<GLuint> programs;

	GLuint box;
	GLuint vertexBufferObject;
	GLuint indexBufferObject;
	GLuint vaoObject1, vaoObject2;
	GLuint offsetUniform;
	GLuint colorUniform;

	float zNear, zFar;


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

	void clear();

	void display(std::vector<RigidBody*>& objects, Camera& camera);


	std::string txtToString(std::string fileName);

	GLuint createShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint createProgram(const std::vector<GLuint> &shaderList);

	void initializeProgram(std::vector<GLuint> &programs);
	void initializeVertexBuffer();
	void initializeVertexArrayObjects();

	int isRunning();
};

#endif