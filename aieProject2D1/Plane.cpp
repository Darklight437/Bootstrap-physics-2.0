#include "Plane.h"



Plane::Plane() : PhysicsObject(PLANE)
{
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(PLANE)
{
}


Plane::~Plane()
{
}
