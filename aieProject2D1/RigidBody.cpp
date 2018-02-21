#include "RigidBody.h"





RigidBody::RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
{
	m_velocity = velocity;
	m_mass = mass;
	m_position = position;
	m_rotation = rotation;
	
}

RigidBody::RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float elasticity) : PhysicsObject(shapeID)
{
	m_velocity = velocity;
	m_mass = mass;
	m_position = position;
	m_rotation = rotation;
	m_elasticity = elasticity;
}


RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timestep)
{
	m_velocity -= m_velocity * m_linearDrag * timestep;
	m_velocity += gravity * timestep;

	m_position += m_velocity * timestep;

	m_rotation += m_angularVelocity * timestep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timestep;
	
	//applyForce(gravity * m_mass * timestep, m_position);

	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD )
	{
		m_velocity = glm::vec2(0, 0);
	}
	if (glm::abs(m_angularVelocity) < MIN_ROTATIONAL_THRESHOLD)
	{
		m_angularVelocity = 0;
	}

	
	
}

void RigidBody::debug()
{
}

void RigidBody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	m_velocity += (force / m_mass);
	m_angularVelocity += (force.y * pos.x - force.x * pos.y) / (m_moment);

}

//void RigidBody::applyForceToActor(RigidBody * actor2, glm::vec2 force)
//{
//	actor2->applyForce(force);
//	applyForce(-force);
//
//}

void RigidBody::resolveCollision(RigidBody * actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr)
{
	//resolve the vector between their centres, or use the provided direction
	// of force
	glm::vec2 normal = collisionNormal ? *collisionNormal : glm::normalize(actor2->m_position - m_position);
	
	//get the vector perpendicular to the collision normal
	glm::vec2 pNormal(normal.y, -normal.x);

	//determine the total velocity of the contact point
	//for both linear and rotational velocity

	//r is the radius from axis to application of force
	float r1 = glm::dot(contact - m_position, -pNormal);
	float r2 = glm::dot(contact - actor2->m_position, pNormal);

	//velocity of the contact point on this object
	float v1 = glm::dot(m_velocity, normal) - r1 * m_rotation;

	// velocity of contact point on actor2
	float v2 = glm::dot(actor2->m_velocity, normal) + r2 * actor2->m_rotation;

	if (v1 > v2) //objects are approaching eachother
	{
		// calculate the effective mass at contact point for each object
		// ie how much the contact point will move due to the force applied.
		float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / m_moment);
		float mass2 = 1.0f / (1.0f / actor2->m_mass + (r2*r2) / actor2->m_moment);

		float elasticity = (m_elasticity + actor2->getElasticity()) * 0.5f;

		glm::vec2 force = (1.0f + elasticity)*mass1*mass2 / (mass1 + mass2)*(v1 - v2)*normal;

		//apply equal and opposite forces
		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->m_position);
	}

}
