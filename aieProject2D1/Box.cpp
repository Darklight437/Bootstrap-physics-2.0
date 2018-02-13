#include "Box.h"
#include <Gizmos.h>


Box::Box(glm::vec2 position, glm::vec2 velocity, glm::vec2 maxDimentions, float mass,
	 glm::vec4 colour) : RigidBody(BOX, position, velocity, 0, mass)
{
	m_position = position;
	m_velocity = velocity;
	m_dimentions = maxDimentions;
	m_mass = mass;
	m_colour = colour;
}


Box::~Box()
{
}

void Box::makeGizmo()
{
	aie::Gizmos::add2DAABB(m_position, m_dimentions, m_colour);
}

void Box::fixedUpdate(glm::vec2 gravity, float timestep)
{
	m_position += m_velocity * timestep;
	applyForce(gravity * m_mass * timestep);
}

glm::vec2 Box::getCorner(int corner)
{
	float m_width = m_dimentions.x;
	float m_height = m_dimentions.y;

	glm::vec2 cornerPos = m_position;

	switch (corner)
	{
	case 1:
		
		cornerPos.x -= m_width;
		cornerPos.y += m_height;
		break;
	case 2:
		
		cornerPos.x += m_width;
		cornerPos.y += m_height;
		break;
	case 3:
		
		cornerPos.x -= m_width;
		cornerPos.y -= m_height;
		break;
	case 4:
		
		cornerPos.x += m_width;
		cornerPos.y -= m_height;
		break;
	default:
		
		break;
	}


	return cornerPos;
}

void Box::applyForce(glm::vec2 force)
{
	m_velocity += force;
}
