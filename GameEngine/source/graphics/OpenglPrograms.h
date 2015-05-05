#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace OpenglPrograms
{
	// Program for meshes with positions and normals. Colors are uniforms.
	extern GLuint dsPN;
	// Program for meshes with positions, normals and texture coordinates.
	// Diffuse and specular colors are read from textures.
	extern GLuint dsPNTxDS;
	// Program for meshes with positions, normals and texture coordinates.
	// Diffuse color is read from texture. Specular color is a uniform.
	extern GLuint dsPNTxD;
	// Program for point lights.
	extern GLuint dsLightPoint;
	// Program for spotlights.
	extern GLuint dsLightSpot;
	// Program for directional lights.
	extern GLuint dsLightDirectional;

	// Initialize every program.
	void init();
	// Initialize opengl program for displaying objects with textures.
	void initProgramdsPNTxDS();
	// Initialize opengl program for displaying objects with a uniform material.
	void initProgramdsPN();
	// Initialize opengl program for displaying point lights.
	void initProgramdsLightPoint();
	// Initialize opengl program for displaying spotlights.
	void initProgramdsLightSpot();
	// Initialize opengl program for displaying directional lights.
	void initProgramdsLightDirectional();

	std::string txtToString(std::string fileName);

	GLuint createShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint createProgram(const std::vector<GLuint> &shaderList);
}