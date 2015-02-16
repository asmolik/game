
#include "Mesh.h"


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}


void Mesh::loadMesh(std::string fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName.c_str(),
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_JoinIdenticalVertices);
	if (!scene)
		std::cout << "Import failed." << std::endl << importer.GetErrorString() << std::endl;

	simpleMeshes.resize(scene->mNumMeshes);
	for (int i = 0; i < scene->mNumMeshes; ++i)
	{
		loadSimpleMesh(i, scene->mMeshes[i], scene->mMaterials[i]);
	}
}


void Mesh::loadSimpleMesh(int index, const aiMesh* mesh, const aiMaterial* material)
{
	if (mesh->HasTextureCoords(0))
		loadPNTx(index, mesh);
	else
		loadPN(index, mesh);

	loadMaterial(index, material);
}


void Mesh::loadPN(int index, const aiMesh* mesh)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	vertices.resize(mesh->mNumVertices * 6);
	indices.resize(mesh->mNumFaces * 3);

	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		const aiVector3D* pos = &mesh->mVertices[i];
		const aiVector3D* nor = &mesh->mNormals[i];

		vertices.push_back(pos->x);
		vertices.push_back(pos->y);
		vertices.push_back(pos->z);
		vertices.push_back(nor->x);
		vertices.push_back(nor->y);
		vertices.push_back(nor->z);
	}

	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		const aiFace* face = &mesh->mFaces[i];
		indices.push_back(face->mIndices[0]);
		indices.push_back(face->mIndices[1]);
		indices.push_back(face->mIndices[2]);
	}

	simpleMeshes[index].loadMeshPN(vertices, indices);
}


void Mesh::loadPNTx(int index, const aiMesh* mesh)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	vertices.resize(mesh->mNumVertices * 8);
	indices.resize(mesh->mNumFaces * 3);

	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		const aiVector3D* pos = &mesh->mVertices[i];
		const aiVector3D* nor = &mesh->mNormals[i];
		const aiVector3D* tex = &mesh->mTextureCoords[0][i];

		vertices.push_back(pos->x);
		vertices.push_back(pos->y);
		vertices.push_back(pos->z);
		vertices.push_back(nor->x);
		vertices.push_back(nor->y);
		vertices.push_back(nor->z);
		vertices.push_back(tex->x);
		vertices.push_back(tex->y);
	}

	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		const aiFace* face = &mesh->mFaces[i];
		indices.push_back(face->mIndices[0]);
		indices.push_back(face->mIndices[1]);
		indices.push_back(face->mIndices[2]);
	}

	simpleMeshes[index].loadMeshPNTx(vertices, indices);
}


void Mesh::loadMaterial(int index, const aiMaterial* material)
{
	//Material has diffuse and specular textures.
	if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0 &&
		material->GetTextureCount(aiTextureType_SPECULAR) > 0)
		loadMaterialDS(index, material);
	//Material has only diffuse texture.
	else if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		loadMaterialD(index, material);
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

		GLuint diffuseUnif = glGetUniformLocation(OpenglPrograms::dsPN, "diffuseColor");
		GLuint specularUnif = glGetUniformLocation(OpenglPrograms::dsPN, "specularColor");
		GLuint shininessUnif = glGetUniformLocation(OpenglPrograms::dsPN, "shininessFactor");
		mat.setUniforms(diffuseUnif, specularUnif, shininessUnif);
		simpleMeshes[index].setMaterial(mat);
	}
}


void Mesh::loadMaterialDS(int index, const aiMaterial* material)
{
	Material mat;
	aiString path;

	material->GetTexture(aiTextureType_DIFFUSE, 0, &path, 0, 0, 0, 0, 0);
	Texture* diffuseTexture = new Texture(0);
	diffuseTexture->loadTextureSRGB(std::string(path.C_Str()));
	mat.setDiffuseTexture(diffuseTexture);

	material->GetTexture(aiTextureType_SPECULAR, 0, &path, 0, 0, 0, 0, 0);
	Texture* specularTexture = new Texture(1);
	specularTexture->loadTextureSRGB(std::string(path.C_Str()));
	mat.setSpecularTexture(specularTexture);

	float shininess;
	material->Get(AI_MATKEY_SHININESS, shininess);
	mat.setShininess(shininess);

	GLuint diffuseUnif = glGetUniformLocation(OpenglPrograms::dsPNTxDS, "diffuseColorSampler");
	GLuint specularUnif = glGetUniformLocation(OpenglPrograms::dsPNTxDS, "specularColorSampler");
	GLuint shininessUnif = glGetUniformLocation(OpenglPrograms::dsPNTxDS, "shininessFactor");
	mat.setUniforms(diffuseUnif, specularUnif, shininessUnif);
	simpleMeshes[index].setMaterial(mat);
}


void Mesh::loadMaterialD(int index, const aiMaterial* material)
{
	Material mat;
	aiString path;

	material->GetTexture(aiTextureType_DIFFUSE, 0, &path, 0, 0, 0, 0, 0);
	Texture* diffuseTexture = new Texture(0);
	diffuseTexture->loadTextureSRGB(std::string(path.C_Str()));
	mat.setDiffuseTexture(diffuseTexture);

	aiColor3D color;
	material->Get(AI_MATKEY_COLOR_SPECULAR, color);
	glm::vec3 specularColor(color.r, color.b, color.b);
	mat.setSpecularColor(specularColor);

	float shininess;
	material->Get(AI_MATKEY_SHININESS, shininess);
	mat.setShininess(shininess);

	GLuint diffuseUnif = glGetUniformLocation(OpenglPrograms::dsPNTxD, "diffuseColorSampler");
	GLuint specularUnif = glGetUniformLocation(OpenglPrograms::dsPNTxD, "specularColor");
	GLuint shininessUnif = glGetUniformLocation(OpenglPrograms::dsPNTxD, "shininessFactor");
	mat.setUniforms(diffuseUnif, specularUnif, shininessUnif);
	simpleMeshes[index].setMaterial(mat);
}


void Mesh::display()
{
	for (SimpleMesh& mesh : simpleMeshes)
		mesh.display();
}
