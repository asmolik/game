
#include "Contact.h"

Contact::Contact() : body1(0), body2(0) {}

Contact::Contact(RigidBody* b1, RigidBody* b2, glm::vec3 n, float d, float t) : body1(b1), body2(b2), normal(n), distance(d), timeOfImpact(t) {}