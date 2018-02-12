#include "Sphere.h"
#include <Gizmos.h>
#include <iostream>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass,
	float radius, glm::vec4 colour) : RigidBody(CIRCLE, position, velocity, 0, mass)
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
	applyForce(gravity * m_mass * timestep);
	
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour);

}

bool Sphere::checkCollision(PhysicsObject * pOther)
{
	//glm::vec2 otherPos;
	//float otherRad;
	//if (dynamic_cast<Sphere*>(pOther) != nullptr)
	//{
	//	otherPos = dynamic_cast<Sphere*>(pOther)->getPosition();
	//	otherRad = dynamic_cast<Sphere*>(pOther)->getRadius();
	//}
	//glm::vec2 distanceBetween = m_position - otherPos;
	//
	//if (glm::distance( m_position , otherPos) <= (m_radius + otherRad))
	//{
	//	glm::vec2 separateTeleport(glm::normalize(distanceBetween).x * 0.1 , 0);
	//	std::cout << glm::distance(m_position, otherPos) << std::endl;
	//	dynamic_cast<Sphere*>(pOther)->m_position -= separateTeleport;
	//	return true;
	//}

	//return false;
}
