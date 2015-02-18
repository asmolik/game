#pragma once
#include <GL/glew.h>

namespace OpenglPrograms
{
	//Program for meshes with positions and normals. Colors are uniforms.
	extern GLuint dsPN;
	/*
	Program for meshes with positions, normals and texture coordinates.
	Diffuse and specular colors are read from textures.
	*/
	extern GLuint dsPNTxDS;
	/*
	Program for meshes with positions, normals and texture coordinates.
	Diffuse color is read from texture. Specular color is a uniform.
	*/
	extern GLuint dsPNTxD;

	void setPN(GLuint program);
	void setPNTxDS(GLuint program);
	void setPNTxD(GLuint program);
}