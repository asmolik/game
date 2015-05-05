
#ifndef TRACK_H
#define TRACK_H

#include "RigidBody.h"
#include "Contact.h"

class Track : public RigidBody
{
private:
	glm::vec3 normal;
	glm::mat4 worldMat;

	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint diffuseTexture;
	static GLuint specularTexture;
	static GLuint normalTexture;
	static GLuint vao;

	static GLuint matrixUnif;
	static GLuint worldMatrixUnif;

	static GLuint diffuseTextureUnif;
	static GLuint specularTextureUnif;
	static GLuint normalTextureUnif;
	static GLuint shininessFactorUnif;

public:
	Track();

	static void init(GLuint program);

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);
	void displayLights(glutil::MatrixStack &matrix, glm::mat4& cameraTransform);

	glm::vec3 getNormal();

	void setNormal(glm::vec3& n);

	static const float vertexPositions[156];
	static const short indexData[36];
};

#endif