#include "OBB.h"



OBB::OBB(glm::vec2 position, glm::vec2 velocity, glm::vec2 maxDimentions, float mass, float rotation,
	glm::vec4 colour) : RigidBody(BOX, position, velocity, rotation, mass)
{
}


OBB::~OBB()
{
}
