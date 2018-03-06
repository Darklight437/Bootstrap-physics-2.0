#pragma once
#include "RigidBody.h"
#include <vector>
class Polygon :
	public RigidBody
{
public:
	Polygon(glm::vec2 position, glm::vec2 velocity, float mass, float radius, int points);
	~Polygon();

	glm::vec2 getpoint(int index);

protected:


	void calculateNormals();
	void makeGizmo();

	std::vector<glm::vec2> m_points;
	std::vector<glm::vec2> normals;
	glm::vec4 m_colour = glm::vec4(1, 0, 0, 1);
	std::vector<glm::vec2> localPoint;
	std::vector<glm::vec2> localNormals;
	
};

