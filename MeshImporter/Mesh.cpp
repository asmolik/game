#include "Mesh.h"
using namespace MeshImporter;

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}


// Load a mesh from a file with assimp.
void Mesh::loadMesh(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName.c_str(),
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenNormals |
		aiProcess_FlipWindingOrder);
	if (!scene)
	{
		std::cout << "Import failed." << std::endl << importer.GetErrorString() << std::endl;
		return;
	}

	simpleMeshes.resize(scene->mNumMeshes);
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		loadSimpleMesh(i, scene->mMeshes[i], scene->mMaterials[i]);
	}
}


// Save this mesh to a file which can be opened by the game engine.
int Mesh::saveMesh(const std::string& fileName)
{
	std::ofstream file;
	file.open(fileName);
	if (!file.is_open())
	{
		std::cout << "Unable to open output file." << std::endl;
		return 1;
	}

	// Write the xml header.
	file << "<?xml version=\"1.0\" encoding=\"utf - 8\"?>" << std::endl;

	file << "<Mesh>" << std::endl;
	for (SimpleMesh& mesh : simpleMeshes)
		mesh.saveMesh(file);
	file << "</Mesh>" << std::endl;
	return 0;
}





void Mesh::loadSimpleMesh(int index, const aiMesh* mesh, const aiMaterial* material)
{
	if (mesh->HasTextureCoords(0))
		loadPNTx(index, mesh);
	else
		loadPN(index, mesh);

	//loadMaterial(index, material);
}


void Mesh::loadPN(int index, const aiMesh* mesh)
{
	float* vertices;
	unsigned int* indices;
	vertices = new float[mesh->mNumVertices * 6];
	indices = new unsigned int[mesh->mNumFaces * 3];

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		const aiVector3D* pos = &mesh->mVertices[i];
		const aiVector3D* nor = &mesh->mNormals[i];

		unsigned int index = i * 6;
		vertices[index++] = (pos->x);
		vertices[index++] = (pos->y);
		vertices[index++] = (pos->z);
		vertices[index++] = (nor->x);
		vertices[index++] = (nor->y);
		vertices[index++] = (nor->z);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		const aiFace* face = &mesh->mFaces[i];
		unsigned int index = i * 3;
		indices[index++] = (face->mIndices[0]);
		indices[index++] = (face->mIndices[1]);
		indices[index++] = (face->mIndices[2]);
	}

	simpleMeshes[index].loadMeshPN(vertices, indices, mesh->mNumVertices * 6, mesh->mNumFaces * 3);
}


void Mesh::loadPNTx(int index, const aiMesh* mesh)
{
	float* vertices;
	unsigned int* indices;
	vertices = new float[mesh->mNumVertices * 8];
	indices = new unsigned int[mesh->mNumFaces * 3];

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		const aiVector3D* pos = &mesh->mVertices[i];
		const aiVector3D* nor = &mesh->mNormals[i];
		const aiVector3D* tex = &mesh->mTextureCoords[0][i];

		unsigned int index = i * 6;
		vertices[index++] = (pos->x);
		vertices[index++] = (pos->y);
		vertices[index++] = (pos->z);
		vertices[index++] = (nor->x);
		vertices[index++] = (nor->y);
		vertices[index++] = (nor->z);
		vertices[index++] = (tex->x);
		vertices[index++] = (tex->y);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		const aiFace* face = &mesh->mFaces[i];
		unsigned int index = i * 3;
		indices[index++] = (face->mIndices[0]);
		indices[index++] = (face->mIndices[1]);
		indices[index++] = (face->mIndices[2]);
	}

	simpleMeshes[index].loadMeshPNTx(vertices, indices, mesh->mNumVertices * 8, mesh->mNumFaces * 3);
}


void Mesh::loadMaterial(int index, const aiMaterial* material)
{
	//Material has diffuse and specular textures.
	if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
		material->GetTextureCount(aiTextureType_SPECULAR) > 0)
	{
		loadMaterialDS(index, material);
	}
	//Material has only diffuse texture.
	else if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
	{
		loadMaterialD(index, material);
	}
	//No textures.
	else
	{
		Material mat;
		aiColor3D color;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		glm::vec3 diffuseColor(color.r, color.b, color.b);
		mat.setDiffuseColor(diffuseColor);

		material->Get(AI_MATKEY_COLOR_SPECULAR, color);
		glm::vec3 specularColor(color.r, color.b, color.b);
		mat.setSpecularColor(specularColor);

		float shininess;
		material->Get(AI_MATKEY_SHININESS, shininess);
		mat.setShininess(shininess);

		simpleMeshes[index].setMaterial(mat);
	}
}


void Mesh::loadMaterialDS(int index, const aiMaterial* material)
{
	Material mat;
	aiString path;

	material->GetTexture(aiTextureType_DIFFUSE, 0, &path, 0, 0, 0, 0, 0);
	mat.setDiffuseTexture(std::string(path.C_Str()));

	material->GetTexture(aiTextureType_SPECULAR, 0, &path, 0, 0, 0, 0, 0);
	mat.setSpecularTexture(std::string(path.C_Str()));

	float shininess;
	material->Get(AI_MATKEY_SHININESS, shininess);
	mat.setShininess(shininess);

	simpleMeshes[index].setMaterial(mat);
}


void Mesh::loadMaterialD(int index, const aiMaterial* material)
{
	Material mat;
	aiString path;

	material->GetTexture(aiTextureType_DIFFUSE, 0, &path, 0, 0, 0, 0, 0);
	mat.setDiffuseTexture(std::string(path.C_Str()));

	aiColor3D color;
	material->Get(AI_MATKEY_COLOR_SPECULAR, color);
	glm::vec3 specularColor(color.r, color.b, color.b);
	mat.setSpecularColor(specularColor);

	float shininess;
	material->Get(AI_MATKEY_SHININESS, shininess);
	mat.setShininess(shininess);

	simpleMeshes[index].setMaterial(mat);
}


CSMeshImporter::CSMeshImporter()
{
	mesh = new Mesh();
}


CSMeshImporter::~CSMeshImporter()
{
	delete mesh;
	mesh = 0;
}


void CSMeshImporter::loadMesh(System::String ^fileName)
{
	mesh->loadMesh(msclr::interop::marshal_as<std::string>(fileName));
}


void CSMeshImporter::saveMesh(System::String ^fileName)
{
	mesh->saveMesh(msclr::interop::marshal_as<std::string>(fileName));
}
