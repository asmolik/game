#pragma once
#include "windows.h"
#include <msclr\marshal_cppstd.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include <iostream>
#include "SimpleMesh.h"

namespace MeshImporter
{
	class Mesh
	{
	protected:
		std::vector<SimpleMesh> simpleMeshes;

	public:
		Mesh();
		~Mesh();
		// Load a mesh from a file with assimp.
		void loadMesh(const std::string& fileName);
		// Save this mesh to a file which can be opened by the game engine.
		int saveMesh(const std::string& fileName);

	protected:
		void loadSimpleMesh(int index, const aiMesh* mesh, const aiMaterial* material);
		// Load a mesh with positions and normals.
		void loadPN(int index, const aiMesh* mesh);
		// Load a mesh with positions, normals and texture coordinates.
		void loadPNTx(int index, const aiMesh* mesh);
		// Load material for the mesh.
		void loadMaterial(int index, const aiMaterial* material);
		// Load material with diffuse and specular textures.
		void loadMaterialDS(int index, const aiMaterial* material);
		// Load material with diffuse texture.
		void loadMaterialD(int index, const aiMaterial* material);
	};

	public ref class CSMeshImporter
	{
	private:
		Mesh* mesh;
	public:
		CSMeshImporter();
		~CSMeshImporter();

		void loadMesh(System::String ^fileName);
		void saveMesh(System::String ^fileName);
	};
}

