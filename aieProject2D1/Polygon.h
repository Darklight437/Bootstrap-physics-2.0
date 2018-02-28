#pragma once
#include "RigidBody.h"
#include <vector>
class Polygon :
	public RigidBody
{
public:
	Polygon(glm::vec2 position, glm::vec2 velocity, float mass);
	~Polygon();

	glm::vec2 getpoint(int);

protected:


	void calculateNormals();


	std::vector<glm::vec2> points;
	std::vector<glm::vec2> normals;

	std::vector<glm::vec2> localPoint;
	std::vector<glm::vec2> localNormals;
};

