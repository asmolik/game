#include "OpenglPrograms.h"


void OpenglPrograms::init()
{
	initProgramdsPNTxDS();
	initProgramdsPN();
	initProgramdsLightPoint();
	initProgramdsLightSpot();
	initProgramdsLightDirectional();
}


// Initialize opengl program for displaying objects with textures.
void OpenglPrograms::initProgramdsPNTxDS()
{
	// Create the shaders and program
	std::vector<GLuint> shaderList;
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsGeometryVertexTex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsGeometryFragmentTex.txt")));

	dsPNTxDS = createProgram(shaderList);

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	// Bind uniform buffer
	GLuint uniformBlockIndex = glGetUniformBlockIndex(dsPNTxDS, "matrices");
	glUniformBlockBinding(dsPNTxDS, uniformBlockIndex, 0);
}


// Initialize opengl program for displaying objects with a uniform material.
void OpenglPrograms::initProgramdsPN()
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsGeometryVertex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsGeometryFragment.txt")));

	dsPN = createProgram(shaderList);

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();

	// Bind uniform buffer
	GLuint uniformBlockIndex = glGetUniformBlockIndex(dsPN, "matrices");
	glUniformBlockBinding(dsPN, uniformBlockIndex, 0);
}


// Initialize opengl program for displaying point lights.
void OpenglPrograms::initProgramdsLightPoint()
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsLightingVertex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsLightingFragmentPoint.txt")));

	dsLightPoint = createProgram(shaderList);

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();
}


// Initialize opengl program for displaying spotlights.
void OpenglPrograms::initProgramdsLightSpot()
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsLightingVertex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsLightingFragmentSpot.txt")));

	dsLightSpot = createProgram(shaderList);

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();
}


// Initialize opengl program for displaying directional lights.
void OpenglPrograms::initProgramdsLightDirectional()
{
	std::vector<GLuint> shaderList;
	shaderList.push_back(createShader(GL_VERTEX_SHADER, txtToString("dsLightingVertex.txt")));
	shaderList.push_back(createShader(GL_FRAGMENT_SHADER, txtToString("dsLightingFragmentDir.txt")));

	dsLightDirectional =  createProgram(shaderList);

	for (GLuint& i : shaderList)
		glDeleteShader;

	shaderList.clear();
}


std::string OpenglPrograms::txtToString(std::string fileName)
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


GLuint OpenglPrograms::createShader(GLenum eShaderType, const std::string &strShaderFile)
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


GLuint OpenglPrograms::createProgram(const std::vector<GLuint> &shaderList)
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


GLuint OpenglPrograms::dsPN = 0;
GLuint OpenglPrograms::dsPNTxDS = 0;
GLuint OpenglPrograms::dsPNTxD = 0;
GLuint OpenglPrograms::dsLightPoint = 0;
GLuint OpenglPrograms::dsLightSpot = 0;
GLuint OpenglPrograms::dsLightDirectional = 0;