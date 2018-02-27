#include "Polygon.h"



Polygon::Polygon(glm::vec2 position, glm::vec2 velocity, float mass) :RigidBody(BOX, position, velocity, 0, mass)
{
}


Polygon::~Polygon()
{
}
