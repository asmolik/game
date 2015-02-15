
#pragma once
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include <iostream>
#include "SimpleMesh.h"

class Mesh
{
protected:
	std::vector<SimpleMesh> simpleMeshes;

public:
	Mesh();
	~Mesh();
	void loadMesh(std::string fileName);
	void display();

protected:
	void loadSimpleMesh(int index, const aiMesh* mesh, const aiMaterial* material);
	void loadPN(int index, const aiMesh* mesh);
	void loadPNTx(int index, const aiMesh* mesh);
	void loadMaterial(int index, const aiMaterial* material);
};

