#include "GameEngine.h"

int main()
{
	GameEngine game;
	Plane map;
	Track track;
	track.setMass(0);
	track.setRestitution(0.9f);
	track.setStaticFriction(0.9f);
	track.setDynamicFriction(0.8f);
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
	car.setInertia(200.0f);
	car.setRestitution(0.3f);
	Wheel w;
	w.setPosition(glm::vec3(708.0f, 5.5f, 505.0f));
	w.setMass(5.0f);
	w.setRestitution(0.7f);
	w.setInertia(1.0f);
	w.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
	w.setStaticFriction(0.5f);
	w.setDynamicFriction(0.5f);
	game.addCar(car);
	game.addPlane(map);
	game.addBody(track);
	game.addBody(box);
	//game.addBody(w);
	game.init();
	game.run();
	return 0;
}