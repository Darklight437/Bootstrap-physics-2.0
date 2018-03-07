#include "Polygon.h"
#include <Gizmos.h>
#include <algorithm>
#include <iostream>

//note size is from the midle to the point
Polygon::Polygon(glm::vec2 position, glm::vec2 velocity, float mass, float radius, int numpoints, glm::vec4 colour) :RigidBody(POLY, position, velocity, 0, mass)
{

	for (int i = 0; i < numpoints; i++)
	{
		//TODO
		//Use this to rotate normals in calculatelocalNormals
		float theta = glm::radians(i * 360 / (float)numpoints);

		float sn = sinf(theta);
		float cs = cosf(theta);

		glm::vec2 currentpoint(sn, -cs);

		currentpoint *= -radius;

		m_points.push_back(currentpoint);

	}
	//translate points into relative local space
	for (unsigned int i = 0; i < m_points.size(); i++)
	{
		
			m_localPoints.push_back(m_points[i] + m_position);
		
	}

	m_colour = colour;
}


Polygon::~Polygon()
{
}

glm::vec2 Polygon::getpoint(unsigned int index)
{
	if (index < m_points.size())
	{
		return m_points[index];
	}
	else
	{
		std::cout << "tried to acces a point out of array \n";
	}
	
	return glm::vec2(0);
}
//hands out the local points but calculated live
std::vector<glm::vec2> Polygon::getLocalPointsInWorldSpace()
{
	
	std::vector<glm::vec2> lPoints;
	for (unsigned int i = 0; i < m_localPoints.size(); i++)
	{
		lPoints.push_back(m_position + m_localPoints[i]);
	}
	return lPoints;
}

void Polygon::reCalculateLocalPoints()
{
	for (unsigned int i = 0; i < m_points.size(); i++)
	{
		m_localPoints[i] =  (m_points[i] + m_position);
	}
}



void Polygon::calculateNormals()
{
	//currently feels like this wont cover all cases but should work
	
	unsigned int sidesNum = m_points.size();

	for (unsigned int i = 0; i < sidesNum- 1; i++)
	{
		//get the vector between current vrtx and the next one
		glm::vec2 currSide = m_points[i] - m_points[i + 1];

		//convert to a normal
		glm::vec2 normalV = glm::vec2(currSide.y, -currSide.x);
		//normalise
		glm::normalize(normalV);

		m_normals.push_back(normalV);
	}

	if (m_normals.size() < sidesNum)
	{
		glm::vec2 finalSide = glm::vec2(m_points[sidesNum - 1] - m_points[sidesNum]);

		//convert
		glm::vec2 finalNormal = glm::vec2(finalSide.y, -finalSide.x);
		glm::normalize(finalNormal);
		m_normals.push_back(finalNormal);
	}
}

void Polygon::makeGizmo()
{
	for (unsigned int i = 0; i < m_localPoints.size(); i++)
	{
		glm::vec2 p1 = m_localPoints[i];
		glm::vec2 p2 = (m_localPoints[i == m_localPoints.size() - 1 ? 0 : i + 1]);

		aie::Gizmos::add2DTri(m_position, p1, p2, m_colour);
	}

}

void Polygon::fixedUpdate(glm::vec2 gravity, float timestep)
{
	//handle motion

	RigidBody::fixedUpdate(gravity, timestep);
	//update the position of the vertex points
	reCalculateLocalPoints();
}

void Polygon::calculateLocalNormals()
{
	//rotate these

}
