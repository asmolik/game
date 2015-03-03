
#pragma once
#include "GL/glew.h"
#include <SOIL.h>
#include <iostream>
#include <string>

/*
Opengl texture.
*/
class Texture
{
protected:
	GLuint texture;
	int textureUnit;

public:
	Texture();
	Texture(int textureUnit);
	~Texture();

	// Load a texture from a file.
	void loadTextureSRGB(std::string fileName);
	//Set the default texture unit for this texture.
	void setTextureUnit(int textureUnit);
	
	GLuint getTexture();
	// Bind this texture for reading in opengl. It is bound to this texture's texture unit.
	void bind();
	// Bind this texture for reading in opengl. It is bound to specified texture unit.
	// @param textureUnit texture unit to bind this texture to.
	void bind(int textureUnit);
};

