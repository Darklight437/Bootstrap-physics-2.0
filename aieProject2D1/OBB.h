#pragma once
#include "RigidBody.h"
class OBB :
	public RigidBody
{
public:
	OBB(glm::vec2 position, glm::vec2 velocity, glm::vec2 maxDimentions, float mass, float rotation,
		glm::vec4 colour);
	~OBB();


	 void fixedUpdate(glm::vec2 gravity, float timestep);
	 void makeGizmo();
	 float getWidth() { return m_maxDimentions.x; }
	 float getHeight() { return m_maxDimentions.y; }
	 glm::vec2 getMaxDimentions() { return m_maxDimentions; }
	 glm::vec2 getLocalX() { return m_localX; }
	 glm::vec2 getLocalY() { return m_localY; }
protected:

	glm::vec2 m_maxDimentions = glm::vec2(0);
	glm::vec4 m_colour = glm::vec4(0, 0, 0, 1);

	glm::vec2 m_localX = glm::vec2(1);
	glm::vec2 m_localY = glm::vec2(1);
};

