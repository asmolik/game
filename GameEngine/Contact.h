
#ifndef CONTACT_H
#define CONTACT_H

class RigidBody;

#include <glm/vec3.hpp>

class Contact
{
protected:
	RigidBody* body1;
	RigidBody* body2;
	//Points to body2.
	glm::vec3 normal;
	//Point of impact on body1.
	glm::vec3 point1;
	//Point of impact on body2.
	glm::vec3 point2;
	float distance;
	float timeOfImpact;

public:
	Contact();
	Contact(RigidBody* b1, RigidBody* b2, glm::vec3 normal, float distance, float timeOfImpact);

	void setBody1(RigidBody* body);
	void setBody2(RigidBody* body);
	void setNormal(glm::vec3& normal);
	void setDistance(float distance);
	void setTimeOfImpact(float time);
	void set(RigidBody* body1, RigidBody* body2, glm::vec3& normal, glm::vec3& point1, glm::vec3& point2, float distance, float time);

	RigidBody* getBody1();
	RigidBody* getBody2();
	glm::vec3 getNormal();
	glm::vec3 getPoint1();
	glm::vec3 getPoint2();
	float getDistance();
	float getTimeOfImpact();
};

#endif