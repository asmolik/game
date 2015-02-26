#pragma once
#include <vector>
#include "Material.h"

namespace MeshImporter
{
	class SimpleMesh
	{
	protected:
		int numberOfVertices;
		int numberOfIndices;
		float* vertices;
		unsigned int* indices;

		Material material;

	public:
		SimpleMesh();
		~SimpleMesh();

		// Load mesh with positions and normals.
		void loadMeshPN(float* vertices, unsigned int* indices, int v, int i);
		// Load mesh with positions, normals and texture coordinates.
		void loadMeshPNTx(float* vertices, unsigned int* indices, int v, int i);
		// Set material for this mesh.
		void setMaterial(Material& material);

		// Print this mesh to the specified stream.
		void saveMesh(std::ostream& os);
	};
}

