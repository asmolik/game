#include "SimpleMesh.h"


SimpleMesh::SimpleMesh()
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	glGenVertexArrays(1, &vao);
	numberOfIndices = 0;
}


SimpleMesh::~SimpleMesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vao);
}


void SimpleMesh::loadMeshPN(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* indices.size(), &indices[0], GL_STATIC_DRAW);
	numberOfIndices = indices.size();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 8, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 8, (void*)(sizeof(float)* 3));

	glBindVertexArray(0);
}


void SimpleMesh::loadMeshPNTx(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* indices.size(), &indices[0], GL_STATIC_DRAW);
	numberOfIndices = indices.size();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 8, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 8, (void*)(sizeof(float)* 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float)* 8, (void*)(sizeof(float)* 6));

	glBindVertexArray(0);
}


void SimpleMesh::setMaterial(Material& mat)
{
	material = mat;
}


void SimpleMesh::display()
{
	material.load();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
