
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class Ball;
class Plane;

#include <ctime>
#include <vector>
#include "Physics.h"
#include "OpenglRenderer.h"
#include "Input.h"
#include "RigidBody.h"
#include "Plane.h"
#include "Track.h"
#include "Box.h"
#include "Wheel.h"
#include "Car.h"
#include "Contact.h"


class GameEngine
{
private:
	float timeStep;
	std::vector<RigidBody*> bodies;
	std::vector<RigidBody*> balls;
	//cars
	std::vector<Car> cars;
	std::vector<RigidBody*> planes;
	Track track;
	
	glm::vec3 gravity;

	bool freeCamera; //free camera if true, locked behind a car if not
	Camera camera;

	Car* controlledCar;

	double mouseX, mouseY;

	Input input;
	OpenglRenderer renderer;

public:
	GameEngine();
	GameEngine(float timeStep);

	void init();

	void addBody(RigidBody& body);
	void addCar(Car& car);
	void addBall(Ball& ball);
	void addPlane(Plane& plane);

	/*void createObject();
	void deleteObject();*/

	/*
	static void errorCallback();
	void errorCallbackImpl();

	static void keyCallback();
	void keyCallbackImpl();

	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	void windowSizeCallbackImpl(int width, int height);*/


	//void applyExternalForces();
	//void applyImpulse(Contact contact);
	//void solveContacts();
	void integrate();

	glm::vec3 getCameraRightVector();
	glm::vec3 getCameraUpVector();
	glm::vec3 getCameraFrontVector();
	void setCameraVelocity(glm::vec3& v);
	void moveCamera(glm::vec3& v);
	void rotateCamera(glm::vec3& axis, float angleDeg);

	double getMouseX();
	double getMouseY();

	void setMouseX(double x);
	void setMouseY(double y);

	int display();

	void reshapeWindow(int width, int height);

	void run();
};

#endif