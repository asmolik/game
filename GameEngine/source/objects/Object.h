#pragma once
#include "RigidBody.h"
#include "Mesh.h"

/*
Base class for every object with a mesh. By default it is static for the physics engine.
*/
class Object : public RigidBody
{
protected:
	Mesh mesh;
	GLuint matrixUnif;

public:
	Object();
	~Object();

	virtual std::vector<Contact*> generateContact(RigidBody* body);

	/*
	Display this object.
	@param matrix transformation matrix
	*/
	void display(glutil::MatrixStack& matrix);
	void displayLights(glutil::MatrixStack& matrix, glm::mat4& cameraTransform);
	void loadMesh(const std::string& fileName);
};

