
#pragma once
#include <GL/glew.h>
#include <vector>
#include "Material.h"

class SimpleMesh
{
protected:
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vao;
	int numberOfIndices;

	Material material;

public:
	SimpleMesh();
	~SimpleMesh();

	void loadMeshPN(std::vector<float>& vertices, std::vector<unsigned int>& indices);
	void loadMeshPNTx(std::vector<float>& vertices, std::vector<unsigned int>& indices);
	void display();
	void setMaterial(Material& material);
};

