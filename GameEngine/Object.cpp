#include "Object.h"


Object::Object() : RigidBody(ObjectIDs::noPhysicsID)
{
}


Object::~Object()
{
}


std::vector<Contact*> Object::generateContact(RigidBody* body)
{
	return std::vector<Contact*>();
}

void Object::display(glutil::MatrixStack& matrix)
{
	glutil::PushStack push(matrix);

	matrix.Translate(current.position);
	matrix *= glm::mat4_cast(current.orientation);
	glUniformMatrix4fv(matrixUnif, 1, GL_FALSE, glm::value_ptr(matrix.Top()));
	mesh.display();
}


void Object::displayLights(glutil::MatrixStack& matrix, glm::mat4& cameraTransform)
{
}


void Object::loadMesh(const std::string& fileName)
{
	mesh.loadMesh(fileName);
	matrixUnif = glGetUniformLocation(mesh.getProgram(), "modelToCameraMatrix");
}
