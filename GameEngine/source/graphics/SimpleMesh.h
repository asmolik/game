
#pragma once
#include <GL/glew.h>
#include <vector>
#include "Material.h"

/*
Basic mesh with a material.
*/
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

	//Load mesh with positions and normals.
	void loadMeshPN(std::vector<float>& vertices, std::vector<unsigned int>& indices);
	//Load mesh with positions, normals and texture coordinates.
	void loadMeshPNTx(std::vector<float>& vertices, std::vector<unsigned int>& indices);
	//Display this mesh. Appropriate opengl program is assumed to be bound.
	void display();
	//Set material for this mesh.
	void setMaterial(Material& material);
};

