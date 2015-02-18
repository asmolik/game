#include "GameEngine.h"

int main()
{
	Mesh mesh;
	GameEngine game;
	mesh.loadMesh("C:/Users/Olek/Downloads/assimp-3.1.1/test/models/OBJ/box.obj");
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
	box.setPosition(glm::vec3(600.0f, 5.2f, 505.0f));
	box.setForce(glm::vec3(50.0f, 0.0f, 0.0f));
	box.setAngularVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	box.setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));

	glm::vec3 sodiumLightColor(255.0f / 255.0f, 209.0f / 255.0f, 178.0f / 255.0f);
	sodiumLightColor *= 400.0f;
	PointLight l;
	l.set(sodiumLightColor, glm::vec3(600.0f, 5.2f, 507.0f), 1.0f / 15.0f);
	PointLight l2;
	l2.set(glm::vec3(400.0f), glm::vec3(650.0f, 5.2f, 507.0f), 1.0f / 15.0f);
	PointLight l3;
	l3.set(glm::vec3(400.0f), glm::vec3(700.0f, 5.2f, 507.0f), 1.0f / 15.0f);
	PointLight l4;
	l4.set(sodiumLightColor, glm::vec3(550.0f, 5.2f, 507.0f), 1.0f / 15.0f);
	PointLight l5;
	l5.set(sodiumLightColor, glm::vec3(500.0f, 5.2f, 507.0f), 1.0f / 15.0f);
	PointLight l6;
	l6.set(sodiumLightColor, glm::vec3(450.0f, 5.2f, 507.0f), 1.0f / 15.0f);
	PointLight l7;
	l7.set(sodiumLightColor, glm::vec3(450.0f, 4.2f, 515.0f), 1.0f / 30.0f);

	glm::vec3 headLight(209.0f / 255.0f, 209.0f / 255.0f, 255.0f / 255.0f);
	SpotLight sl;
	sl.set(headLight * 800.0f, glm::vec3(800.0f, 0.5f, 505.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f / 50.0f, Physics::degToRad(10.0f));

	Car car;
	car.setPosition(glm::vec3(650.0f, 1.1f, 505.0f));
	car.setMass(1500.0f);
	car.setInertia(200.0f);
	car.setRestitution(0.3f);
	car.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
	//car.setAngularVelocity(glm::vec3(0.0f, 10.8f, 0.0f));
	Wheel w;
	w.setPosition(glm::vec3(800.0f, 5.5f, 505.0f));
	w.setMass(5.0f);
	w.setRestitution(0.7f);
	w.setInertia(1.0f);
	w.rotate(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
	w.setStaticFriction(0.5f);
	w.setDynamicFriction(0.5f);
	game.addPlane(map);
	game.addBody(track);
	game.addCar(car);
	game.addBody(box);
	game.addBody(w);
	game.addPointLight(l);
	game.addPointLight(l2);
	game.addPointLight(l3);
	game.addPointLight(l4);
	game.addPointLight(l5);
	game.addPointLight(l6);
	game.addPointLight(l7);
	game.addSpotLight(sl);
	game.init();
	game.run();
	return 0;
}