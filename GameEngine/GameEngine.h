
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

class Ball;
class Plane;

#include <cmath>
#include <ctime>
#include <vector>
#include "Physics.h"
#include "OpenglRenderer.h"
#include "Input.h"
#include "PhysicsEngine.h"
#include "RigidBody.h"
#include "Plane.h"
#include "Track.h"
#include "Box.h"
#include "Wheel.h"
#include "Car.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Contact.h"
#include "Constraint.h"
#include "PositionConstraint.h"
#include "RotationConstraint.h"


class GameEngine
{
private:
	Input input;
	OpenglRenderer renderer;
	PhysicsEngine physics;

	double gameTime;
	double startHour;
	double dayLength;
	double sunriseTime;
	double sunsetTime;

	float timeStep;
	std::vector<RigidBody*> bodies;
	std::vector<RigidBody*> balls;
	std::vector<Car> cars;
	std::vector<RigidBody*> planes;
	Track track;

	DirectionalLight sun;
	float ambientIntensity;
	std::vector<PointLight> pointLights;
	std::vector<SpotLight> spotLights;
	
	glm::vec3 gravity;

	Camera camera;

	Car* controlledCar;

	double mouseX, mouseY;

public:
	GameEngine();
	GameEngine(float timeStep);

	void init();

	void addBody(RigidBody& body);
	void addCar(Car& car);
	void addBall(Ball& ball);
	void addPlane(Plane& plane);

	void addPointLight(PointLight& pointLight);
	void addSpotLight(SpotLight& spotLight);

	glm::vec3 getCameraRightVector();
	glm::vec3 getCameraUpVector();
	glm::vec3 getCameraFrontVector();
	void setCameraVelocity(glm::vec3& v);
	void moveCamera(glm::vec3& v);
	void rotateCamera(glm::vec3& axis, float angleDeg);
	void changeCameraTarget();

	double getMouseX();
	double getMouseY();

	void setMouseX(double x);
	void setMouseY(double y);

	void calcSun(glm::vec3& sunDirection, glm::vec3& sunColor, glm::vec3& ambient);

	double currentHour();

	int display();

	void reshapeWindow(int width, int height);

	void run();
};

#endif