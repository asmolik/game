#include "OpenglRenderer.h"

void error_callback_o(int error, const char* description)
{
	std::fputs(description, stderr);
}

void key_callback_o(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void windowSizeCallback_o(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


OpenglRenderer::OpenglRenderer(int width, int height, std::string name, void* ptr)
{
	glfwSetErrorCallback(error_callback_o);

	window = createWindow(width, height, name);

	glfwSetWindowUserPointer(window, ptr);

	glfwSetKeyCallback(window, key_callback_o);

	glfwSetWindowSizeCallback(window, windowSizeCallback_o);
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}


	zNear = 0.1f;
	zFar = 3000.0f;

	wWidth = width;
	wHeight = height;

	init();
}


OpenglRenderer::~OpenglRenderer()
{
	delete perspectiveMatrixUB;
}




void OpenglRenderer::init()
{
	initializePrograms();

	perspectiveMatrixUB = new UniformBuffer();
	perspectiveMatrixUB->setSize();
	perspectiveMatrixUB->bind();

	Plane::init(OpenglPrograms::dsPN);
	//Track::init(OpenglPrograms::dsPNTxDS);
	Box::init(OpenglPrograms::dsPN);
	Wheel::init(OpenglPrograms::dsPN);

	SpotLight::init(OpenglPrograms::dsLightSpot);
	Cone::init(OpenglPrograms::dsLightSpot);
	Quad::init(OpenglPrograms::dsLightDirectional);
	Sphere::init(OpenglPrograms::dsLightPoint);

	reshapeWindow(wWidth, wHeight);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(zNear, zFar);
	glEnable(GL_DEPTH_CLAMP);
}

GLFWwindow* OpenglRenderer::createWindow(int width, int height, std::string name)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback_o);

	return window;
}

GLFWwindow* OpenglRenderer::getWindow()
{
	return window;
}

void OpenglRenderer::reshapeWindow(int width, int height)
{
	wWidth = width;
	wHeight = height;
	perspectiveMatrix = glm::perspective(45.0f, (wWidth / (float)wHeight), zNear, zFar);
	perspectiveMatrixUB->setData(perspectiveMatrix, 0);

	glViewport(0, 0, width, height);
}

void OpenglRenderer::setWindowSize(int width, int height)
{
	glfwSetWindowSize(window, width, height);
}


void OpenglRenderer::setWindowUserPointer(void* pointer)
{
	glfwSetWindowUserPointer(window, pointer);
}

void OpenglRenderer::setErrorCallback(void* callback)
{
	glfwSetErrorCallback((GLFWerrorfun)callback);
}

void OpenglRenderer::setCursorPosCallback(void* callback)
{
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)callback);
}

void OpenglRenderer::setKeyCallback(void* callback)
{
	glfwSetKeyCallback(window, (GLFWkeyfun)callback);
}

void OpenglRenderer::setWindowSizeCallback(void* callback)
{
	glfwSetWindowSizeCallback(window, (GLFWwindowsizefun)callback);
}

void OpenglRenderer::setAmbientColor(glm::vec3& c)
{
	ambientColor = c;
}
void OpenglRenderer::setSun(glm::vec3& d, glm::vec3& c)
{
	sunDirection = d;
	sunColor = c;
}


// Set the vector of objects to be displayed.
void OpenglRenderer::setObjects(std::vector<RigidBody*>* objects)
{
	this->objects = objects;
}


//Set the camera with which to display the scene.
void OpenglRenderer::setCamera(Camera* camera)
{
	this->camera = camera;
}



// Set the vector of point lights to be displayed.
void OpenglRenderer::setPointLights(std::vector<PointLight>* pointLights)
{
	this->pointLights = pointLights;
}


// Set the vector of spotlights to be displayed.
void OpenglRenderer::setSpotLights(std::vector<SpotLight>* spotLights)
{
	this->spotLights = spotLights;
}


//
//void OpenglRenderer::display(std::vector<RigidBody*>& objects, Camera& camera)
//{
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//	glClearDepth(1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glutil::MatrixStack matrix(perspectiveMatrix);
//	matrix.ApplyMatrix(camera.cameraTransform());
//
//	glUseProgram(programs[0]);
//
//
//	/*for (RigidBody* obj : objects)
//	{
//		obj->display(perspectiveMatrix);
//	}*/
//
//	glBindVertexArray(vaoObject1);
//	offsetUniform = glGetUniformLocation(programs[0], "offset");
//	glUniform3f(offsetUniform, 0.0f, 0.0f, 0.0f);
//
//	colorUniform = glGetUniformLocation(programs[0], "theColor");
//	glUniform4f(colorUniform, 1.0f, 1.0f, 1.0f, 1.0f);
//
//	GLuint frustumUnif = glGetUniformLocation(programs[0], "perspectiveMatrix");
//	glUniformMatrix4fv(frustumUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
//
//	//draw track
//	//objects[5]->display(matrix);
//
//	for (int i = 2; i < 4; ++i)
//	{
//		glUseProgram(programs[i]);
//
//		//set ambient intensity
//		GLuint ambInt = glGetUniformLocation(programs[i], "ambientColor");
//		glUniform4f(ambInt, ambientColor.x, ambientColor.y, ambientColor.z, 1.0f);
//		//set directional light intensity and direction(sun)
//		GLuint dirLightInt = glGetUniformLocation(programs[i], "sunColor");
//		GLuint dirLightDir = glGetUniformLocation(programs[i], "sunDirection");
//		glUniform4f(dirLightInt, sunColor.x, sunColor.y, sunColor.z, 0.0f);
//		glUniform4f(dirLightDir, sunDirection.x, sunDirection.y, sunDirection.z, 1.0f);
//		GLuint maxInt = glGetUniformLocation(programs[i], "maxIntensity");
//		glUniform1f(maxInt, sunColor.x * 1.3f);
//		//set camera pos
//		GLuint cameraPos = glGetUniformLocation(programs[i], "cameraPos");
//		glUniform4f(cameraPos, camera.getX(), camera.getY(), camera.getZ(), 0.0f);
//	}
//
//	glUseProgram(programs[2]);
//
//	//draw ground
//	glDepthMask(GL_FALSE);
//	objects[0]->display(matrix);
//	glDepthMask(GL_TRUE);
//
//	for (int i = 2; i < objects.size(); ++i)
//	{
//		objects[i]->display(matrix);
//	}
//
//	glUseProgram(programs[3]);
//	objects[1]->display(matrix);
//
//	//draw box
//	//objects[7]->display(matrix);
//
//	//draw wheel
//	//objects[3]->display(matrix);
//
//	//draw car
//	//objects[4]->display(matrix);
//
//
//
//	//draws lolboxes
//	glUseProgram(programs[1]);
//	matrix.Translate(-2.0, 0.5, 0.0);
//
//	glBindVertexArray(vaoObject2);
//	offsetUniform = glGetUniformLocation(programs[1], "offset");
//	glUniform3f(offsetUniform, 0.0f, 0.0f, 5.0f);
//
//	frustumUnif = glGetUniformLocation(programs[1], "matrix");
//	glUniformMatrix4fv(frustumUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
//
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//	offsetUniform = glGetUniformLocation(programs[1], "offset");
//	glUniform3f(offsetUniform, 10.0f, 0.0f, 5.0f);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//	glUseProgram(0);
//	
//	glfwSwapBuffers(window);
//	glfwPollEvents();
//}


void OpenglRenderer::dsDisplay()
{
	dsGeometry();
	dsLighting();

	glfwSwapBuffers(window);
	glfwPollEvents();
}


void OpenglRenderer::dsGeometry()
{
	gbuffer.bindForWriting();
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "FB error, status: 0x%x\n", status);
	}

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutil::MatrixStack matrix(camera->cameraTransform());

	glUseProgram(OpenglPrograms::dsPN);

	//draw ground
	glDepthMask(GL_FALSE);
	objects->at(0)->display(matrix);
	glDepthMask(GL_TRUE);

	for (int i = 2; i < objects->size(); ++i)
	{
		objects->at(i)->display(matrix);
	}
	(*objects)[objects->size() - 1]->display(matrix);

	glUseProgram(OpenglPrograms::dsPNTxDS);
	//objects[1]->display(matrix);

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
}


void OpenglRenderer::dsLighting()
{
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	gbuffer.bindForReading();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	dsLightingPoint();
	dsLightingSpot();
	dsLightingFromObjects();
	dsLightingDirectional();

	
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "lol";

	/*GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "lol";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "FB error, status: 0x%x\n", status);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "lol";
	gbuffer.bindForReading();
	status = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
	err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "lol";
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		fprintf(stderr, "FB error, status: 0x%x\n", status);
	}

	GLsizei hw = (GLsizei)wWidth / 2;
	GLsizei hh = (GLsizei)wHeight / 2;

	gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	glBlitFramebuffer(0, 0, wWidth, wHeight,
		0, 0, hw, hh, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glBlitFramebuffer(0, 0, wWidth, wHeight,
		0, hh, hw, wHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	glBlitFramebuffer(0, 0, wWidth, wHeight,
		hw, hh, wWidth, wHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_SHININESS);
	glBlitFramebuffer(0, 0, wWidth, wHeight,
		hw, 0, wWidth, hh, GL_COLOR_BUFFER_BIT, GL_LINEAR);*/
}


void OpenglRenderer::dsLightingPoint()
{
	glutil::MatrixStack matrix(perspectiveMatrix);
	matrix.ApplyMatrix(camera->cameraTransform());

	glUseProgram(OpenglPrograms::dsLightPoint);

	for (PointLight& p : *pointLights)
	{
		//set light params
		GLuint lightColor = glGetUniformLocation(OpenglPrograms::dsLightPoint, "lightColor");
		GLuint lightPosition = glGetUniformLocation(OpenglPrograms::dsLightPoint, "lightPosition");
		GLuint attenuation = glGetUniformLocation(OpenglPrograms::dsLightPoint, "attenuation");
		GLuint maxInt = glGetUniformLocation(OpenglPrograms::dsLightPoint, "maxIntensity");
		glUniform4f(lightColor, p.getColor().x, p.getColor().y, p.getColor().z, 1.0f);
		glm::vec4 lPos = camera->cameraTransform() * glm::vec4(p.getPosition(), 1.0f);
		glUniform4fv(lightPosition, 1, glm::value_ptr(lPos));
		glUniform1f(attenuation, p.getAttenuation());
		glUniform1f(maxInt, sunColor.x * 1.0f);
		//set screen size
		GLuint screenSize = glGetUniformLocation(OpenglPrograms::dsLightPoint, "screenSize");
		glUniform2f(screenSize, (float)wWidth, (float)wHeight);
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
			std::cout << "lol";

		float scale = 2 / p.getAttenuation();
		glutil::PushStack push(matrix);
		matrix.Translate(p.getPosition());
		Sphere::display(matrix, scale);
	}
}


void OpenglRenderer::dsLightingSpot()
{
	glm::mat4 camT = camera->cameraTransform();
	glutil::MatrixStack matrix(perspectiveMatrix);
	matrix.ApplyMatrix(camT);

	glUseProgram(OpenglPrograms::dsLightSpot);

	for (SpotLight& s : *spotLights)
	{
		//set light params
		s.display(camT);
		GLuint maxInt = glGetUniformLocation(OpenglPrograms::dsLightSpot, "maxIntensity");
		glUniform1f(maxInt, sunColor.x * 1.0f);
		//set screen size
		GLuint screenSize = glGetUniformLocation(OpenglPrograms::dsLightSpot, "screenSize");
		glUniform2f(screenSize, (float)wWidth, (float)wHeight);
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
			std::cout << "lol";

		float scale = 2 / s.getAttenuation();
		glutil::PushStack push(matrix);
		matrix.Translate(s.getPosition());
		Cone::display(matrix, scale);
	}
}


void OpenglRenderer::dsLightingDirectional()
{
	glUseProgram(OpenglPrograms::dsLightDirectional);

	//set ambient intensity
	GLuint ambInt = glGetUniformLocation(OpenglPrograms::dsLightDirectional, "ambientColor");
	GLenum err = glGetError();
	if (err != GL_NO_ERROR || ambInt == -1)
		std::cout << "lol";

	glUniform4f(ambInt, ambientColor.x, ambientColor.y, ambientColor.z, 1.0f);
	//set directional light intensity and direction(sun)
	GLuint dirLightInt = glGetUniformLocation(OpenglPrograms::dsLightDirectional, "sunColor");
	GLuint dirLightDir = glGetUniformLocation(OpenglPrograms::dsLightDirectional, "sunDirection");
	glUniform4f(dirLightInt, sunColor.x, sunColor.y, sunColor.z, 0.0f);
	glm::vec4 sunDir = camera->cameraTransform() * glm::vec4(sunDirection, 0.0f);
	glUniform4fv(dirLightDir, 1, glm::value_ptr(sunDir));
	GLuint maxInt = glGetUniformLocation(OpenglPrograms::dsLightDirectional, "maxIntensity");
	glUniform1f(maxInt, sunColor.x * 1.0f);
	//set screen size
	GLuint screenSize = glGetUniformLocation(OpenglPrograms::dsLightDirectional, "screenSize");
	glUniform2f(screenSize, (float)wWidth, (float)wHeight);

	glm::mat4 mat(1.0f);
	glutil::MatrixStack matrix(mat);

	Quad::display(matrix);
}


void OpenglRenderer::dsLightingFromObjects()
{
	glm::mat4 camT = camera->cameraTransform();
	glutil::MatrixStack matrix(perspectiveMatrix);
	matrix.ApplyMatrix(camT);

	glUseProgram(OpenglPrograms::dsLightSpot);
	for (RigidBody* object : *objects)
	{
		object->displayLights(matrix, camT);
	}
}


void OpenglRenderer::initializePrograms()
{
	OpenglPrograms::init();
}

void OpenglRenderer::initializeDS()
{
	gbuffer.init(wWidth, wHeight);
}

int OpenglRenderer::isRunning()
{
	if (!glfwWindowShouldClose(window))
		return 1;
	return 0;
}
