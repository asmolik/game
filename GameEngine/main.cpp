#include "GameEngine.h"

int main()
{
	GameEngine game;
	Plane map;
	Track track;
	Box box;
	box.setMass(1000.0f);
	box.setInertia(10.0f);
	box.setPosition(glm::vec3(600.0f, 10.2f, 505.0f));
	box.setForce(glm::vec3(50.0f, 0.0f, 0.0f));
	box.setAngularVelocity(glm::vec3(0.0f, 10.0f, 0.0f));
	Wheel wheel;
	Car car;
	car.setPosition(glm::vec3(700.0f, 1.0f, 505.0f));
	car.setMass(1500.0f);
	car.setInertia(100.0f);
	game.addPlane(map);
	game.addBody(track);
	game.addBody(box);
	game.addBody(wheel);
	game.addCar(car);
	game.init();
	game.run();
	return 0;
}