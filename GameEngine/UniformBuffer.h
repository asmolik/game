#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformBuffer
{
protected:
	GLuint buffer;

public:
	UniformBuffer();
	~UniformBuffer();
	// Sets default size of the buffer (std140, 2*sizeof(glm::mat4))
	void setSize();
	void setSize(size_t size);
	void setData(glm::mat4& matrix, int index);
};

