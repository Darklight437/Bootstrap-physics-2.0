#include "Sphere.h"
#include <Gizmos.h>
#include <iostream>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass,
	float radius, glm::vec4 colour) : RigidBody(CIRCLE, position, velocity, 0, mass)
{
	
	m_radius = radius;
	m_colour = colour;
	m_moment = (2 / 5) * m_mass * (m_radius * m_radius);
	
}

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float elasticity, glm::vec4 colour)
	: RigidBody(CIRCLE, position, velocity, 0, mass, elasticity)
{
	m_radius = radius;
	m_colour = colour;
}


Sphere::~Sphere()
{
}



void Sphere::makeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) *m_radius;

	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1- m_colour.x, 1 - m_colour.y, 1 - m_colour.z, 1));

}


