#include "UniformBuffer.h"


UniformBuffer::UniformBuffer()
{
	glGenBuffers(1, &buffer);
	bindingPoint = 0;
}


UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &buffer);
}


// Sets default size of the buffer (std140, 2*sizeof(glm::mat4))
void UniformBuffer::setSize()
{
	size = 2 * sizeof(glm::mat4);
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
	glBufferData(GL_UNIFORM_BUFFER, size , 0, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void UniformBuffer::setSize(size_t size)
{
	this->size = size;
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
	glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_STREAM_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void UniformBuffer::setData(glm::mat4& matrix, int index)
{
	glBindBuffer(GL_UNIFORM_BUFFER, buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, index * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrix));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void UniformBuffer::bind()
{
	glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, buffer, 0, size);
}
