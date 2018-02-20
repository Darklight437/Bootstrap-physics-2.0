#include "Plane.h"
#include <glm\ext.hpp>
#include <Gizmos.h>
#include "RigidBody.h"

Plane::Plane() : PhysicsObject(PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(PLANE)
{
	m_normal = glm::normalize(normal);
	m_distanceToOrigin = distance;
}


Plane::~Plane()
{
}

void Plane::fixedUpdate(glm::vec2 gravity, float timestep)
{
}

void Plane::makeGizmo()
{
	float lineSegementLength = 300;
	glm::vec2 centrePoint = m_normal * m_distanceToOrigin;

	//easy to rotate normal through 90 degrees around z
	glm::vec2 paralell(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centrePoint + (paralell * lineSegementLength);
	glm::vec2 end = centrePoint - (paralell * lineSegementLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

void Plane::resetPosition()
{
}

void Plane::resolveCollision(RigidBody * actor2, glm::vec2 position)
{
	glm::vec2 normal = m_normal;
	glm::vec2 relativeVeclocity = actor2->getVelocity();
	//confirm if objects are moving towards eachother


	float elasticity = (actor2->getElasticity()) ;

	float j = glm::dot(-(1 + elasticity) * (relativeVeclocity), normal) /
		glm::dot(normal, normal * ((1 / actor2->getMass())));

	glm::vec2 force = normal * j;

	actor2->applyForce(force , position);
	
}
