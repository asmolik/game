
#ifndef GBUFFER_H
#define GBUFFER_H

#include <GL/glew.h>
#include <iostream>


#define GBUFFER_POSITION_TEXTURE_UNIT 0
#define GBUFFER_DIFFUSE_TEXTURE_UNIT 1
#define GBUFFER_SPECULAR_TEXTURE_UNIT 2
#define GBUFFER_NORMAL_TEXTURE_UNIT 3
#define GBUFFER_TEXCOORD_TEXTURE_UNIT 4
#define GBUFFER_SHININESS_TEXTURE_UNIT 5

//delete texcoord
class GBuffer
{
public:
	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_SPECULAR,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_TEXCOORD,
		GBUFFER_TEXTURE_TYPE_SHININESS,
		GBUFFER_NUM_TEXTURES
	};

private:
	GLuint fbo;
	GLuint textures[GBUFFER_NUM_TEXTURES];
	GLuint depthTexture;

public:
	GBuffer();

	~GBuffer();

	bool init(int windowWidth, int windowHeight);

	void bindForReading();
	void bindForWriting();

	void setReadBuffer(GBUFFER_TEXTURE_TYPE textureType);
};


#endif