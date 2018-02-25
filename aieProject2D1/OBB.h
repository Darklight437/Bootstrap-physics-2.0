#pragma once
#include "RigidBody.h"
class OBB :
	public RigidBody
{
public:
	OBB(glm::vec2 position, glm::vec2 velocity, glm::vec2 maxDimentions, float mass,
		glm::vec4 colour);
	~OBB();
};

