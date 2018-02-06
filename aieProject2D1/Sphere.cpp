#include "Sphere.h"
#include <Gizmos.h>


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
	applyForce(gravity * m_mass * timestep);
	m_position += m_velocity * timestep;
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 20, m_colour);

}

bool Sphere::checkCollision(PhysicsObject * pOther)
{
	glm::vec2 otherPos;
	float otherRad;
	if (dynamic_cast<Sphere*>(pOther) != nullptr)
	{
		otherPos = dynamic_cast<Sphere*>(pOther)->getPosition();
		otherRad = dynamic_cast<Sphere*>(pOther)->getRadius();
	}
	glm::vec2 distanceBetween = m_position - otherPos;
	
	if ((distanceBetween.length()) < (m_radius + otherRad))
	{
		return true;
	}

	return false;
}
