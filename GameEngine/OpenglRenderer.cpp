
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

	init();
}




void OpenglRenderer::init()
{
	initializeProgram(programs);
	initializeVertexBuffer();
	initializeVertexArrayObjects();

	Track::init(programs[0]);

	Box::init(programs[2]);

	Wheel::init(programs[2]);


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
	perspectiveMatrix = glm::perspective(45.0f, (width / (float)height), zNear, zFar);

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

void OpenglRenderer::display(std::vector<RigidBody*>& objects, Camera& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutil::MatrixStack matrix(perspectiveMatrix);
	matrix.ApplyMatrix(camera.cameraTransform());

	glutil::PushStack push(matrix);

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
	
	matrix.Translate(objects[0]->getPosition());

	GLuint frustumUnif = glGetUniformLocation(programs[0], "perspectiveMatrix");
	glUniformMatrix4fv(frustumUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
	//draw ground
	glDepthMask(GL_FALSE);
	glDrawElements(GL_TRIANGLES, sizeof(Plane::planeIndexData) / sizeof(short), GL_UNSIGNED_SHORT, 0);
	glDepthMask(GL_TRUE);

	//draw track
	objects[1]->display(matrix);

	glUseProgram(programs[2]);

	//draw box
	objects[2]->display(matrix);

	//draw wheel
	//objects[3]->display(matrix);

	//draw car
	objects[4]->display(matrix);



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

	//car program
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("VertexShaderNormals.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("FragmentShader.txt")));

	programs.push_back(createProgram(shaderList));

	for (GLuint& i : shaderList)
		glDeleteShader;

	perspectiveMatrix = glm::perspective(45.0f, (1280.0f / 720.0f), zNear, zFar);

	glUseProgram(programs[0]);
	GLuint frustumUnif = glGetUniformLocation(programs[0], "perspectiveMatrix");
	glUniformMatrix4fv(frustumUnif, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	glUseProgram(0);
}

void OpenglRenderer::initializeVertexBuffer()
{
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Plane::planeVertexPositions), Plane::planeVertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferObject);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Plane::planeIndexData), Plane::planeIndexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


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

int OpenglRenderer::isRunning()
{
	if (!glfwWindowShouldClose(window))
		return 1;
	return 0;
}