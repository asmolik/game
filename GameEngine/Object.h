#pragma once
#include "RigidBody.h"
#include "Mesh.h"

class Object : public RigidBody
{
protected:
	Mesh mesh;
	GLuint matrixUnif;

public:
	Object();
	~Object();

	virtual std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack& matrix);
	void displayLights(glutil::MatrixStack& matrix, glm::mat4& cameraTransform);
	void loadMesh(const std::string& fileName);
};

