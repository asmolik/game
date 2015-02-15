
#pragma once
#include "GL/glew.h"
#include <SOIL.h>
#include <iostream>
#include <string>

class Texture
{
protected:
	GLuint texture;
	int textureUnit;

public:
	Texture();
	Texture(int textureUnit);
	~Texture();

	void loadTextureSRGB(std::string fileName);
	void setTextureUnit(int textureUnit);
	
	GLuint getTexture();
	void bind();
	void bind(int textureUnit);
};

