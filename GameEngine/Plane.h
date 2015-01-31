
#ifndef PLANE_H
#define PLANE_H

#include "RigidBody.h"
#include "Contact.h"

class Plane : public RigidBody
{
private:
	glm::vec3 normal;
	glm::mat4 worldMat;

	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	static GLuint matrixUnif;
	static GLuint worldMatrixUnif;
	static GLuint diffuseColorUnif;
	static GLuint specularColorUnif;
	static GLuint shininessFactorUnif;

public:
	Plane();

	static void init(GLuint program);

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);
	void displayLights(glutil::MatrixStack &matrix, glm::mat4& cameraTransform);

	glm::vec3 getNormal();

	void setNormal(glm::vec3& n);

	static const float vertexPositions[28];
	static const short indexData[6];
};

#endif