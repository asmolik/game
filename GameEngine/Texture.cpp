
#include "Texture.h"


Texture::Texture()
{
	glGenTextures(1, &texture);
	textureUnit = 0;
}

Texture::Texture(int texUnit)
{
	glGenTextures(1, &texture);
	textureUnit = texUnit;
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}


void Texture::loadTextureSRGB(std::string fileName)
{
	int width = 0, height = 0;
	unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
}


GLuint Texture::getTexture()
{
	return GLuint();
}


void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
}


void Texture::bind(int texUnit)
{
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
}


void Texture::setTextureUnit(int texUnit)
{
	textureUnit = texUnit;
}


