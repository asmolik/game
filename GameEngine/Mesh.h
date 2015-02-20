#pragma once
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include <iostream>
#include "SimpleMesh.h"
#include "OpenglPrograms.h"

/*
Mesh imported with assimp. Can contain multiple simple meshes, but they all have to 
use the same opengl program (neither this class nor the SimpleMesh class change current 
opengl program).
*/
class Mesh
{
protected:
	std::vector<SimpleMesh> simpleMeshes;
	GLuint program;

public:
	Mesh();
	~Mesh();
	//Load mesh from a file with assimp.
	void loadMesh(const std::string& fileName);
	//Display this mesh. Appropriate opengl program is assumed to be bound.
	void display();
	GLuint getProgram();

protected:
	void loadSimpleMesh(int index, const aiMesh* mesh, const aiMaterial* material);
	void loadPN(int index, const aiMesh* mesh);
	void loadPNTx(int index, const aiMesh* mesh);
	void loadMaterial(int index, const aiMaterial* material);
	void loadMaterialDS(int index, const aiMaterial* material);
	void loadMaterialD(int index, const aiMaterial* material);
};

