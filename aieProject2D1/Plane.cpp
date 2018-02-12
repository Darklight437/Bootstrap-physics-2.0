#include "Plane.h"
#include <glm\vec4.hpp>
#include <Gizmos.h>

Plane::Plane() : PhysicsObject(PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(PLANE)
{
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
