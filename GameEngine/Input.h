
#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Car.h"
#include "Camera.h"

class Input
{
private:
	GLFWwindow* window;
	bool key[GLFW_KEY_LAST];
	double oldMouseX, oldMouseY;
	double newMouseX, newMouseY;

public:
	Input();

	void init(GLFWwindow* window);

	static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

	void forwardKey(int key, int action);
	void forwardCursorPos(double xpos, double ypos);


	int action();
	void action(Car* car);
	void action(Camera& cam);
};

#endif