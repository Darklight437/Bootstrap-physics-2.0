#include "Sphere.h"
#include <Gizmos.h>
#include <iostream>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass,
	float radius, glm::vec4 colour) : RigidBody(CIRCLE, position, velocity, 0, mass)
{
	
	m_radius = radius;
	m_colour = colour;
	
}

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float elasticity, glm::vec4 colour) : RigidBody(CIRCLE, position, velocity, 0, mass, elasticity)
{
	m_radius = radius;
	m_colour = colour;
}


Sphere::~Sphere()
{
}

void Sphere::fixedUpdate(glm::vec2 gravity, float timestep)
{
	m_position += m_velocity * timestep;
	
	
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour);

}


