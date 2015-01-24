
#ifndef BOX_H
#define BOX_H

#include "RigidBody.h"
#include "Contact.h"

class Box : public RigidBody
{
private:
	glm::vec3 size;
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
	Box();

	static void init(GLuint program);

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);

	glm::vec3 getSize();

	void setSize(glm::vec3& size);

	static const float vertexPositions[168];
	static const short indexData[36];
};

#endif