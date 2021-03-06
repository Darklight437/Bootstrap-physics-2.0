#pragma once
#include "RigidBody.h"
#include <vector>
class Polygon :
	public RigidBody
{
public:
	Polygon(glm::vec2 position, glm::vec2 velocity, float mass, float radius, int points, glm::vec4 colour);
	~Polygon();

	glm::vec2 getpoint(unsigned int index);
	std::vector<glm::vec2> getLocalPointsInWorldSpace();
	void reCalculateLocalPoints();
	std::vector<glm::vec2> getLocalNormals() { return m_localNormals; }

protected:


	void calculateNormals();
	void makeGizmo();
	void fixedUpdate(glm::vec2 gravity, float timestep);
	void calculateLocalNormals();

	std::vector<glm::vec2> m_points;
	std::vector<glm::vec2> m_normals;
	glm::vec4 m_colour = glm::vec4(1, 0, 0, 1);
	std::vector<glm::vec2> m_localPoints;
	std::vector<glm::vec2>m_localNormals;
	
};

