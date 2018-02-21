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
	

	//get the vector perpendicular to the collision normal
	glm::vec2 pNormal(m_normal.y, -m_normal.x);

	//determine the total velocity of the contact point
	//for both linear and rotational velocity

	//r is the radius from axis to application of force
	float rOther = glm::dot(position - actor2->getPosition(), pNormal);

	//velocity of the contact point on this object (it's stationary)
	glm::vec2 v1(0);

	// velocity of contact point on actor2
	glm::vec2 v2 = -actor2->getVelocity();

	//if (v1 > v2) //objects are approaching eachother
	
		// calculate the effective mass at contact point for each object
		// ie how much the contact point will move due to the force applied.
		
		float mass2 = 1.0f / (1.0f / actor2->getMass() + (rOther * rOther) / actor2->getMomentOfInertia());

		float elasticity = (actor2->getElasticity());
		//the magnitude of the impulse force
		float impulse = glm::dot(-(1.0f + elasticity) * v2, m_normal) / glm::dot(m_normal, m_normal * actor2->getMass());
		glm::vec2 force(v2 + (impulse / actor2->getMass()) * m_normal);
		

		//apply equal and opposite forces
		
		actor2->applyForce(force, position - actor2->getPosition());
	


}
