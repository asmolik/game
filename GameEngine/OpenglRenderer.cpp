
#include "OpenglRenderer.h"
const float vertexData[] ={
	0.25f, 0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,

	0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,

	0.25f, 0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,

	0.25f, 0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,

	0.25f, 0.25f, -1.25f, 1.0f,
	0.25f, 0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,

	0.25f, 0.25f, -2.75f, 1.0f,
	0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,

	0.25f, 0.25f, -2.75f, 1.0f,
	-0.25f, 0.25f, -1.25f, 1.0f,
	-0.25f, 0.25f, -2.75f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,




	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

};

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




void OpenglRenderer::init()
{
	initializeProgram(programs);
	initializeVertexBuffer();
	initializeVertexArrayObjects();

	Plane::init(programs[4]);

	Track::init(programs[5]);

	Box::init(programs[4]);

	Wheel::init(programs[4]);

	Quad::init(programs[6]);
	Sphere::init(programs[7]);


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

void OpenglRenderer::clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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

void OpenglRenderer::display(std::vector<RigidBody*>& objects, Camera& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutil::MatrixStack matrix(perspectiveMatrix);
	matrix.ApplyMatrix(camera.cameraTransform());

	glUseProgram(programs[0]);


	/*for (RigidBody* obj : objects)
	{
		obj->display(perspectiveMatrix);
	}*/

	glBindVertexArray(vaoObject1);
	offsetUniform = glGetUniformLocation(programs[0], "offset");
	glUniform3f(offsetUniform, 0.0f, 0.0f, 0.0f);

	colorUniform = glGetUniformLocation(programs[0], "theColor");
	glUniform4f(colorUniform, 1.0f, 1.0f, 1.0f, 1.0f);

	GLuint frustumUnif = glGetUniformLocation(programs[0], "perspectiveMatrix");
	glUniformMatrix4fv(frustumUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));

	//draw track
	//objects[5]->display(matrix);

	for (int i = 2; i < 4; ++i)
	{
		glUseProgram(programs[i]);

		//set ambient intensity
		GLuint ambInt = glGetUniformLocation(programs[i], "ambientColor");
		glUniform4f(ambInt, ambientColor.x, ambientColor.y, ambientColor.z, 1.0f);
		//set directional light intensity and direction(sun)
		GLuint dirLightInt = glGetUniformLocation(programs[i], "sunColor");
		GLuint dirLightDir = glGetUniformLocation(programs[i], "sunDirection");
		glUniform4f(dirLightInt, sunColor.x, sunColor.y, sunColor.z, 0.0f);
		glUniform4f(dirLightDir, sunDirection.x, sunDirection.y, sunDirection.z, 1.0f);
		GLuint maxInt = glGetUniformLocation(programs[i], "maxIntensity");
		glUniform1f(maxInt, sunColor.x * 1.3f);
		//set camera pos
		GLuint cameraPos = glGetUniformLocation(programs[i], "cameraPos");
		glUniform4f(cameraPos, camera.getX(), camera.getY(), camera.getZ(), 0.0f);
	}

	glUseProgram(programs[2]);

	//draw ground
	glDepthMask(GL_FALSE);
	objects[0]->display(matrix);
	glDepthMask(GL_TRUE);

	for (int i = 2; i < objects.size(); ++i)
	{
		objects[i]->display(matrix);
	}

	glUseProgram(programs[3]);
	objects[1]->display(matrix);

	//draw box
	//objects[7]->display(matrix);

	//draw wheel
	//objects[3]->display(matrix);

	//draw car
	//objects[4]->display(matrix);



	//draws lolboxes
	glUseProgram(programs[1]);
	matrix.Translate(-2.0, 0.5, 0.0);

	glBindVertexArray(vaoObject2);
	offsetUniform = glGetUniformLocation(programs[1], "offset");
	glUniform3f(offsetUniform, 0.0f, 0.0f, 5.0f);

	frustumUnif = glGetUniformLocation(programs[1], "matrix");
	glUniformMatrix4fv(frustumUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	offsetUniform = glGetUniformLocation(programs[1], "offset");
	glUniform3f(offsetUniform, 10.0f, 0.0f, 5.0f);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}


void OpenglRenderer::dsDisplay(std::vector<RigidBody*>& objects, std::vector<PointLight>& pLights, std::vector<SpotLight>& sLights, Camera& camera)
{
	dsGeometry(objects, camera);
	dsLighting(pLights, sLights, camera);

	glfwSwapBuffers(window);
	glfwPollEvents();
}
void OpenglRenderer::dsGeometry(std::vector<RigidBody*>& objects, Camera& camera)
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

	glutil::MatrixStack matrix(perspectiveMatrix);
	matrix.ApplyMatrix(camera.cameraTransform());

	for (int i = 4; i < 6; ++i)
	{
		glUseProgram(programs[i]);
		
		//set camera pos
		GLuint cameraPos = glGetUniformLocation(programs[i], "cameraPos");
		glUniform4f(cameraPos, camera.getX(), camera.getY(), camera.getZ(), 0.0f);
	}

	glUseProgram(programs[4]);

	//draw ground
	glDepthMask(GL_FALSE);
	objects[0]->display(matrix);
	glDepthMask(GL_TRUE);

	for (int i = 2; i < objects.size(); ++i)
	{
		objects[i]->display(matrix);
	}

	glUseProgram(programs[5]);
	objects[1]->display(matrix);

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
}
void OpenglRenderer::dsLighting(std::vector<PointLight>& pLights, std::vector<SpotLight>& sLights, Camera& camera)
{
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	gbuffer.bindForReading();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	dsLightingPoint(pLights, camera);
	dsLightingDirectional(camera);

	
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
void OpenglRenderer::dsLightingPoint(std::vector<PointLight>& pLights, Camera& camera)
{
	glutil::MatrixStack matrix(perspectiveMatrix);
	matrix.ApplyMatrix(camera.cameraTransform());

	glUseProgram(programs[7]);

	for (PointLight& p : pLights)
	{
		//set light params
		GLuint lightColor = glGetUniformLocation(programs[7], "lightColor");
		GLuint lightPosition = glGetUniformLocation(programs[7], "lightPosition");
		GLuint attenuation = glGetUniformLocation(programs[7], "attenuation");
		GLuint maxInt = glGetUniformLocation(programs[7], "maxIntensity");
		glUniform4f(lightColor, p.getColor().x, p.getColor().y, p.getColor().z, 1.0f);
		glUniform4f(lightPosition, p.getPosition().x, p.getPosition().y, p.getPosition().z, 1.0f);
		glUniform1f(attenuation, p.getAttenuation());
		glUniform1f(maxInt, sunColor.x * 1.0f);
		//set camera pos
		GLuint cameraPos = glGetUniformLocation(programs[7], "cameraPos");
		glUniform4f(cameraPos, camera.getX(), camera.getY(), camera.getZ(), 0.0f);
		//set screen size
		GLuint screenSize = glGetUniformLocation(programs[7], "screenSize");
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
void OpenglRenderer::dsLightingDirectional(Camera& camera)
{
	glUseProgram(programs[6]);

	//set ambient intensity
	GLuint ambInt = glGetUniformLocation(programs[6], "ambientColor");
	GLenum err = glGetError();
	if (err != GL_NO_ERROR || ambInt == -1)
		std::cout << "lol";

	glUniform4f(ambInt, ambientColor.x, ambientColor.y, ambientColor.z, 1.0f);
	//set directional light intensity and direction(sun)
	GLuint dirLightInt = glGetUniformLocation(programs[6], "sunColor");
	GLuint dirLightDir = glGetUniformLocation(programs[6], "sunDirection");
	glUniform4f(dirLightInt, sunColor.x, sunColor.y, sunColor.z, 0.0f);
	glUniform4f(dirLightDir, sunDirection.x, sunDirection.y, sunDirection.z, 1.0f);
	GLuint maxInt = glGetUniformLocation(programs[6], "maxIntensity");
	glUniform1f(maxInt, sunColor.x * 1.0f);
	//set camera pos
	GLuint cameraPos = glGetUniformLocation(programs[6], "cameraPos");
	glUniform4f(cameraPos, camera.getX(), camera.getY(), camera.getZ(), 0.0f);
	//set screen size
	GLuint screenSize = glGetUniformLocation(programs[6], "screenSize");
	glUniform2f(screenSize, (float)wWidth, (float)wHeight);

	glm::mat4 mat(1.0f);
	glutil::MatrixStack matrix(mat);

	Quad::display(matrix);
}



std::string OpenglRenderer::txtToString(std::string fileName)
{
	std::ifstream file(fileName);
	std::string line;
	std::string txt;
	if (!file.is_open())
		return txt;

	while (std::getline(file, line))
		txt.append(line + '\n');

	file.close();

	return txt;
}

GLuint OpenglRenderer::createShader(GLenum eShaderType, const std::string &strShaderFile)
{
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType)
		{
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

GLuint OpenglRenderer::createProgram(const std::vector<GLuint> &shaderList)
{
	GLuint program = glCreateProgram();

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);

	return program;
}

void OpenglRenderer::initializeProgram(std::vector<GLuint> &programs)
{
	std::vector<GLuint> shaderList;

	//plane and track program
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("VertexShader.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("FragmentShader.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	//cool box program
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("VertexShader2.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("FragmentShader2.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	//program[2]
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("VertexShaderNormals.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("FragmentShaderNormals.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	//program[3] - texture
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("VertexShaderTextureBump.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("FragmentShaderTextureBump.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	//program[4] - dsgeo
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsGeometryVertex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsGeometryFragment.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	//program[5] - dsgeotexture
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsGeometryVertexTex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsGeometryFragmentTex.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	//program[6] - dslightdir
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsLightingVertex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsLightingFragmentDir.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	//program[7] - dslightpoint
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsLightingVertex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsLightingFragmentPoint.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();


	perspectiveMatrix = glm::perspective(45.0f, (wWidth / (float)wHeight), zNear, zFar);

	glUseProgram(programs[0]);
	GLuint frustumUnif = glGetUniformLocation(programs[0], "perspectiveMatrix");
	glUniformMatrix4fv(frustumUnif, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	glUseProgram(0);
}

void OpenglRenderer::initializeVertexBuffer()
{
	glGenBuffers(1, &box);

	glBindBuffer(GL_ARRAY_BUFFER, box);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenglRenderer::initializeVertexArrayObjects()
{
	glGenVertexArrays(1, &vaoObject1);
	glBindVertexArray(vaoObject1);

	//size_t colorDataOffset = sizeof(float)* 3 * numberOfVertices;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);

	glGenVertexArrays(1, &vaoObject2);
	glBindVertexArray(vaoObject2);
	
	glBindBuffer(GL_ARRAY_BUFFER, box);

	size_t colorData = sizeof(vertexData) / 2;

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

	glBindVertexArray(0);
}

void OpenglRenderer::initializeUniformBuffer()
{
	glGenBuffers(1, &lightBufferUniform);
	glBindBuffer(GL_UNIFORM_BUFFER, lightBufferUniform);
	glBufferData(lightBufferUniform, sizeof(float), NULL, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	GLuint lightBlock = glGetUniformBlockIndex(programs[2], "Light");
	glUniformBlockBinding(programs[2], lightBlock, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, 0,	lightBufferUniform, 0, sizeof(float));

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