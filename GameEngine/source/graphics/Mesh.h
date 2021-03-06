#pragma once
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include "Xml.h"
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
	//Load mesh from an xml file.
	int loadMesh(const std::string& fileName);
	//Display this mesh. Appropriate opengl program is assumed to be bound.
	void display();
	//A program that is appropriate for this mesh.
	GLuint getProgram();

protected:
	void loadSimpleMesh(int index, const aiMesh* mesh, const aiMaterial* material);
	//Load a mesh with positions and normals.
	void loadPN(int index, const aiMesh* mesh);
	//Load a mesh with positions, normals and texture coordinates.
	void loadPNTx(int index, const aiMesh* mesh);
	//Load material for the mesh.
	void loadMaterial(int index, const aiMaterial* material);
	//Load material with diffuse and specular textures.
	void loadMaterialDS(int index, const aiMaterial* material);
	//Load material with diffuse texture.
	void loadMaterialD(int index, const aiMaterial* material);
};

