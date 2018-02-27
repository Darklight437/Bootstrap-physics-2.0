#pragma once
#include "RigidBody.h"
class Polygon :
	public RigidBody
{
public:
	Polygon(glm::vec2 position, glm::vec2 velocity, float mass);
	~Polygon();





};

