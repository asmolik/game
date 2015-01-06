
#include "GameEngine.h"

GameEngine::GameEngine() : gravity(glm::vec3(0, 9.80665, 0)), timeStep(1.0f / 60.0f), renderer(1600, 900, "Game", this) {}

GameEngine::GameEngine(float t) : gravity(glm::vec3(0, 9.80665, 0)), timeStep(t), renderer(1600, 900, "Game", this) {}

void cursorPosCallback_g(GLFWwindow* window, double xpos, double ypos)
{
	GameEngine* r = (GameEngine*)glfwGetWindowUserPointer(window);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	r->rotateCamera(glm::vec3(0.0f, 1.0f, 0.0f), ((xpos - r->getMouseX()) / 10));
	r->rotateCamera(-r->getCameraRightVector(), ((ypos - r->getMouseY()) / 10));

	r->setMouseX(xpos);
	r->setMouseY(ypos);
	xpos = ypos = 0;
}

void keyCallback_g(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GameEngine* r = (GameEngine*)glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W: r->setCameraVelocity(r->getCameraFrontVector() / 0.01f); break;
		case GLFW_KEY_S: r->setCameraVelocity(-r->getCameraFrontVector() / 0.01f); break;

		case GLFW_KEY_A: r->setCameraVelocity(-r->getCameraRightVector() / 0.01f); break;
		case GLFW_KEY_D: r->setCameraVelocity(r->getCameraRightVector() / 0.01f); break;

		case GLFW_KEY_Q: r->rotateCamera(glm::vec3(0.0f, 0.0f, 1.0f), 5.0f); break;
		case GLFW_KEY_E: r->rotateCamera(glm::vec3(0.0f, 0.0f, 1.0f), -5.0f); break;

		case GLFW_KEY_SPACE: r->setCameraVelocity(glm::vec3(0.0f, 10.0f, 0.0f)); break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		r->setCameraVelocity(glm::vec3(0.0));
	}
}

void windowSizeCallback_g(GLFWwindow* window, int width, int height)
{
	GameEngine* r = (GameEngine*)glfwGetWindowUserPointer(window);
	r->reshapeWindow(width, height);
}

void GameEngine::init()
{
	renderer.setWindowUserPointer(&input);
	renderer.setWindowSizeCallback(windowSizeCallback_g);
	renderer.setCursorPosCallback(Input::glfwCursorPosCallback);
	renderer.setKeyCallback(Input::glfwKeyCallback);

	input.init(renderer.getWindow());

	physics.setTimeStep(1.0f / 60.0f);

	camera.setPosition(glm::vec3(701.0f, 1.0f, 520.0f));
}

void GameEngine::addBody(RigidBody& body)
{
	bodies.push_back(&body);
}

void GameEngine::addCar(Car& car)
{
	controlledCar = &car;
	cars.push_back(car);
	bodies.push_back(&car);
}
/*
void GameEngine::addBall(Ball& ball)
{
	balls.push_back(&ball);
}*/

void GameEngine::addPlane(Plane& plane)
{
	planes.push_back(&plane);
	bodies.push_back(&plane);
}
/*
void GameEngine::applyExternalForces()
{
	for (RigidBody* ball : balls)
	{
		ball->zeroForce();
		ball->applyForce(gravity);
		ball->integrate(timeStep);
	}
}

void GameEngine::solveContacts()
{
	for (RigidBody* ball : balls)
	{
		for (RigidBody* plane : planes)
		{
			Contact contact = ball->generateContact(*plane);
			applyImpulse(contact);
		}
	}
	for (RigidBody* ball1 : balls)
	{
		for (RigidBody* ball2 : balls)
		{
			if (&ball1 != &ball2)
			{
				Contact contact = ball1->generateContact(*ball2);
				applyImpulse(contact);
			}
		}
	}
}

void GameEngine::applyImpulse(Contact contact)
{
	glm::vec3 relativeVelocity(contact.body2->getVelocity() - contact.body1->getVelocity());
	//Relative velocity along the collision's normal.
	float normalVelocity = glm::dot(relativeVelocity, contact.normal);

	//Don't resolve a collision if the bodies aren't moving towards each other.
	if (normalVelocity > 0)
		return;

	//Restitution of collision. Minimum of bodies' restitutions.
	float e = contact.body1->getRestitution() > contact.body2->getRestitution() ? 
		contact.body1->getRestitution() : contact.body2->getRestitution();

	//Strength of the impulse.
	float j = -(1 + e) * normalVelocity;
	j /= contact.body1->getInvMass() + contact.body2->getInvMass();

	glm::vec3 impulse = contact.normal * j;

	//Modify velocities of colliding bodies.
	contact.body1->setVelocity(contact.body1->getVelocity() + (impulse * (-contact.body1->getInvMass())));
	contact.body2->setVelocity(contact.body2->getVelocity() + (impulse * (contact.body2->getInvMass())));

	//friction
	//http://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-friction-scene-and-jump-table--gamedev-7756

	relativeVelocity = contact.body2->getVelocity() - contact.body1->getVelocity();

	glm::vec3 tangent = relativeVelocity - (contact.normal * glm::dot(relativeVelocity, contact.normal));
	//tangent.normalizeThis(); idk

	float jt = -glm::dot(tangent, relativeVelocity);
	jt /= contact.body1->getMass() + contact.body2->getMass();

	float mu = (contact.body1->getStaticFriction() + contact.body2->getStaticFriction()) / 2;

	glm::vec3 frictionImpulse;
	if (std::abs(jt) < j * mu)
		frictionImpulse = tangent * jt;
	else
	{
		mu = (contact.body1->getDynamicFriction() + contact.body2->getDynamicFriction()) / 2;
		frictionImpulse = tangent * (-j * mu);
	}

	contact.body1->setVelocity(contact.body1->getVelocity() + (frictionImpulse * (-contact.body1->getInvMass())));
	contact.body2->setVelocity(contact.body2->getVelocity() + (frictionImpulse * (contact.body2->getInvMass())));
}
*/
void GameEngine::integrate()
{
	camera.move(timeStep);
	for (RigidBody* object : bodies)
	{
		object->update(timeStep);
	}
}

glm::vec3 GameEngine::getCameraRightVector()
{
	return camera.getRightVector();
}
glm::vec3 GameEngine::getCameraUpVector()
{
	return camera.getUpVector();
}
glm::vec3 GameEngine::getCameraFrontVector()
{
	return camera.getFrontVector();
}

void GameEngine::setCameraVelocity(glm::vec3& v)
{
	camera.setVelocity(v);
}

void GameEngine::moveCamera(glm::vec3& v)
{
	camera.move(v);
}

void GameEngine::rotateCamera(glm::vec3& axis, float angleDeg)
{
	camera.rotate(axis, angleDeg);
}

double GameEngine::getMouseX()
{
	return mouseX;
}
double GameEngine::getMouseY()
{
	return mouseY;
}

void GameEngine::setMouseX(double x)
{
	mouseX = x;
}
void GameEngine::setMouseY(double y)
{
	mouseY = y;
}

int GameEngine::display()
{
	renderer.display(bodies, camera);
	return renderer.isRunning();
}

void GameEngine::reshapeWindow(int width, int height)
{
	renderer.reshapeWindow(width, height);
}

void GameEngine::run()
{
	double currentTime = std::clock() / (double)(CLOCKS_PER_SEC / 1000);
	double newTime = currentTime;
	int running = 1;
	while (running)
	{
		//process input
		int c = input.action();
		if (c)
			camera.setObjectToFollow(&controlledCar->box);
		input.action(camera);
		input.action(controlledCar);

		//physics
		double lol = std::clock() / (double)(CLOCKS_PER_SEC / 1000);
		physics.update(bodies);
		camera.move(timeStep);

		//move camera behind the controlled car

		//graphics
		running = display();

		lol = (std::clock() / (double)(CLOCKS_PER_SEC / 1000)) - lol;
		if (lol > timeStep * 1000.0f)
			std::cout << std::fixed << lol << std::endl;
		while ((newTime = std::clock() / (double)(CLOCKS_PER_SEC / 1000)) < (currentTime + timeStep * 1000.0f));
		currentTime = newTime;
	}
}