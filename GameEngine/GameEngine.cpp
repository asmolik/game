
#include "GameEngine.h"

GameEngine::GameEngine() : gravity(glm::vec3(0, 9.80665f, 0)), gameTime(0.0), startHour(8.0), dayLength(1.0 / 144.0),
sunriseTime(6.0), sunsetTime(22.0), timeStep(1.0f / 60.0f), renderer(1600, 900, "Game", this) {}

GameEngine::GameEngine(float t) : gravity(glm::vec3(0, 9.80665f, 0)), timeStep(t), renderer(1600, 900, "Game", this) {}

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
	renderer.initializeDS();
	renderer.setWorld(world);
	renderer.setCamera(&camera);

	input.init(renderer.getWindow());

	physics.setTimeStep(1.0f / 60.0f);

	camera.setPosition(glm::vec3(650.0f, 2.0f, 530.0f));
}


// Read world data from file.
void GameEngine::loadWorld(const std::string& fileName)
{
	world.loadWorld(fileName);
}


void GameEngine::addBody(RigidBody& body)
{
	world.addObject(body);
}

void GameEngine::addCar(Car& car)
{
	controlledCar = &car;
	world.addObject(car);
}

void GameEngine::addPointLight(PointLight& l)
{
	world.addPointLight(l);
}

void GameEngine::addSpotLight(SpotLight& l)
{
	world.addSpotLight(l);
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

void GameEngine::changeCameraTarget()
{
	if (camera.getFollowedObject() == 0)
		camera.setObjectToFollow(controlledCar);
	else
		camera.setObjectToFollow(0);
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

void GameEngine::calcSun(glm::vec3& sunDir, glm::vec3& sunCol, glm::vec3& amb)
{
	double hour = currentHour();
	if (hour > 12.0)
		hour = 24.0 - hour;
	double t = Physics::pi * hour / 24.0;
	sunDir = glm::normalize(glm::vec3(std::cosf(t), -std::sinf(t), 0.0f));
	sunCol = glm::vec3(8000.0f, 8000.0f, 8000.0f);
	sunCol *= (hour / 12.0);
	amb = sunCol / 4.0f;
}

double GameEngine::currentHour()
{
	double time = gameTime / 3600.0;
	time = std::fmod(time, 24.0 * dayLength);
	return time / dayLength;
}

int GameEngine::display()
{
	renderer.dsDisplay();
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
			changeCameraTarget();
		input.action(camera);
		input.action(controlledCar);

		//physics
		double lol = std::clock() / (double)(CLOCKS_PER_SEC / 1000);
		physics.update(world.objects);
		camera.move(timeStep);

		//graphics
		glm::vec3 sunDir, sunCol, ambient;
		calcSun(sunDir, sunCol, ambient);
		renderer.setSun(sunDir, sunCol);
		renderer.setAmbientColor(ambient);
		running = display();

		gameTime += 1.0 / 60.0;

		lol = (std::clock() / (double)(CLOCKS_PER_SEC / 1000)) - lol;
		/*if (lol > timeStep * 1000.0f)
			std::cout << std::fixed << lol << std::endl;*/
		while ((newTime = std::clock() / (double)(CLOCKS_PER_SEC / 1000)) < (currentTime + timeStep * 1000.0f));
		currentTime = newTime;
	}
}
