#include "Box.h"



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
}

void Box::fixedUpdate(glm::vec2 gravity, float timestep)
{
	m_position += m_velocity * timestep;
	applyForce(gravity * m_mass * timestep);
}
