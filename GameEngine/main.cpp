#include "GameEngine.h"

int main()
{
	GameEngine game;
	Plane map;
	Track track;
	track.setMass(0);
	track.setRestitution(0.9f);
	//track.setStaticFriction();
	//track.setDynamicFriction();
	track.setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
	Box box;
	box.setMass(1000.0f);
	box.setInertia(10.0f);
	box.setPosition(glm::vec3(600.0f, 10.2f, 505.0f));
	box.setForce(glm::vec3(50.0f, 0.0f, 0.0f));
	box.setAngularVelocity(glm::vec3(0.0f, 10.0f, 0.0f));
	Car car;
	car.setPosition(glm::vec3(700.0f, 1.5f, 505.0f));
	car.setMass(1500.0f);
	car.setInertia(100.0f);
	car.setRestitution(1.0f);
	game.addCar(car);
	game.addPlane(map);
	game.addBody(track);
	game.addBody(box);
	game.init();
	game.run();
	return 0;
}