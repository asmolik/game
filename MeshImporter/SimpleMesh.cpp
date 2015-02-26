#include "SimpleMesh.h"
using namespace MeshImporter;


SimpleMesh::SimpleMesh()
{
	vertices = 0;
	indices = 0;
	numberOfVertices = 0;
	numberOfIndices = 0;
}


SimpleMesh::~SimpleMesh()
{
	delete[] vertices;
	delete[] indices;
	vertices = 0;
	indices = 0;
}


void SimpleMesh::loadMeshPN(float* vertices, unsigned int* indices, int v, int i)
{
	numberOfVertices = v;
	numberOfIndices = i;
	this->vertices = vertices;
	this->indices = indices;
}


void SimpleMesh::loadMeshPNTx(float* vertices, unsigned int* indices, int v, int i)
{
	numberOfVertices = v;
	numberOfIndices = i;
	this->vertices = vertices;
	this->indices = indices;
}


void SimpleMesh::setMaterial(Material& mat)
{
	material = mat;
}


void SimpleMesh::saveMesh(std::ostream& os)
{
	os << "<SimpleMesh>" << std::endl;
	os << "<Vertices>" << std::endl;
	for (int i = 0; i < numberOfVertices; ++i)
		os << vertices[i] << " ";
	os << std::endl;
	os << "</Vertices>" << std::endl;
	os << "<Indices>" << std::endl;
	for (int i = 0; i < numberOfIndices; ++i)
		os << indices[i] << " ";
	os << std::endl;
	os << "</Indices>" << std::endl;
	os << "</SimpleMesh>" << std::endl;
}
