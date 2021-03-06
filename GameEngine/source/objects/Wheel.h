
#ifndef WHEEL_H
#define WHEEL_H

#include "RigidBody.h"
#include "Plane.h"
#include "Track.h"
#include "Box.h"
#include "Contact.h"
#include <GL/glew.h>

class Wheel : public RigidBody
{
private:
	float radius;
	float height;
	glm::mat4 worldMat;

	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint vao;
	static GLuint matrixUnif;
	static GLuint worldMatrixUnif;
	static GLuint colorUnif;

public:
	Wheel();

	static void init(GLuint program);

	std::vector<Contact*> generateContact(RigidBody* body);

	void display(glutil::MatrixStack &matrix);
	void displayLights(glutil::MatrixStack &matrix, glm::mat4& cameraTransform);

	static const float vertexPositions[2160];
	static const short indexData[362];
};

#endif