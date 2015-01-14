
#include "Input.h"

Input::Input()
{
	for (bool b : key)
		b = false;
}

void Input::init(GLFWwindow* w)
{
	window = w;
	glfwSetKeyCallback(window, Input::glfwKeyCallback);
}

void Input::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input* r = (Input*)glfwGetWindowUserPointer(window);

	r->forwardKey(key, action);
}

void Input::glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Input* r = (Input*)glfwGetWindowUserPointer(window);

	r->forwardCursorPos(xpos, ypos);
}

void Input::forwardKey(int k, int action)
{
	if (action == GLFW_RELEASE)
		key[k] = false;
	else
		key[k] = true;
}

void Input::forwardCursorPos(double x, double y)
{
	newMouseX = x; newMouseY = y;
}


int Input::action()
{
	int ret = 0;
	if (key[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key[GLFW_KEY_C])
		ret = 1;
	return ret;
}

void Input::action(Camera& cam)
{
	cam.rotate(glm::vec3(0.0f, 1.0f, 0.0f), (float)(newMouseX - oldMouseX) / 10.0f);
	cam.rotate(-cam.getRightVector(), (float)(newMouseY - oldMouseY) / 10.0f);

	oldMouseX = newMouseX;
	oldMouseY = newMouseY;

	glm::vec3 camVel;

	if (key[GLFW_KEY_W])
		camVel += cam.getFrontVector() * 100.0f;
	if (key[GLFW_KEY_S])
		camVel -= cam.getFrontVector() * 100.0f;
	if (key[GLFW_KEY_A])
		camVel -= cam.getRightVector() * 100.0f;
	if (key[GLFW_KEY_D])
		camVel += cam.getRightVector() * 100.0f;
	if (key[GLFW_KEY_Q])
		cam.rotate(glm::vec3(0.0f, 0.0f, 1.0f), -5.0f);
	if (key[GLFW_KEY_E])
		cam.rotate(glm::vec3(0.0f, 0.0f, 1.0f), 5.0f);

	cam.setVelocity(camVel);
}

void Input::action(Car* car)
{
	if (car == 0)
		return;

	if (key[GLFW_KEY_UP])
		car->accelerate();
	if (key[GLFW_KEY_DOWN])
		car->brakes();
	if (key[GLFW_KEY_LEFT])
		car->turnLeft();
	if (key[GLFW_KEY_RIGHT])
		car->turnRight();
}