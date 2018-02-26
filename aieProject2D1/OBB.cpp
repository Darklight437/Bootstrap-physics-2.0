#include "OBB.h"
#include <gizmos.h>


OBB::OBB(glm::vec2 position, glm::vec2 velocity, glm::vec2 maxDimentions, float mass, float rotation,
	glm::vec4 colour) : RigidBody(OBOX, position, velocity, rotation, mass)
{

}


OBB::~OBB()
{
}

void OBB::fixedUpdate(glm::vec2 gravity, float timestep)
{
	RigidBody::fixedUpdate(gravity, timestep);

	//store the local axes
	float cos = cosf(m_rotation);
	float sin = sinf(m_rotation);
	m_localX = glm::normalize(glm::vec2(cos, sin));
	m_localY = glm::normalize(glm::vec2(-sin, cos));
}

void OBB::makeGizmo()
{
	// if only using rotation
	// glm::mat4 transform = glm::rotate(m_rotation, glm::vec3(0, 0, 1));
	// aie::Gizmos::add2DAABBFilled(getCenter(),
	// m_extents, m_colour, &transform);


	// draw using local axes
	glm::vec2 p1 = m_position - m_localX * m_maxDimentions.x - m_localY * m_maxDimentions.y;
	glm::vec2 p2 = m_position + m_localX * m_maxDimentions.x - m_localY * m_maxDimentions.y;
	glm::vec2 p3 = m_position - m_localX * m_maxDimentions.x + m_localY * m_maxDimentions.y;
	glm::vec2 p4 = m_position + m_localX * m_maxDimentions.x + m_localY * m_maxDimentions.y;
	aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
	aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
}

