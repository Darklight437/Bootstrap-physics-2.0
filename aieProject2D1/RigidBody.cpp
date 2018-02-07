#include "RigidBody.h"





RigidBody::RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
{
	m_velocity = velocity;
	m_mass = mass;
	m_position = position;
}


RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timestep)
{
	applyForce(gravity * m_mass * timestep);
	m_position += m_velocity * timestep;
}

void RigidBody::debug()
{
}

void RigidBody::applyForce(glm::vec2 force)
{
	m_velocity += (force / m_mass);
}

void RigidBody::applyForceToActor(RigidBody * actor2, glm::vec2 force)
{
	actor2->applyForce(force);
	applyForce(-force);

}
