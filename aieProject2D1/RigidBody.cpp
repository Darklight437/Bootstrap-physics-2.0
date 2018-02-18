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

void RigidBody::resolveCollision(RigidBody * actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVeclocity = actor2->getVelocity() - m_velocity;

	m_elasticity = 1;
	float j = glm::dot(-(1 + m_elasticity) * (relativeVeclocity), normal) /
		glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;

	applyForceToActor(actor2, force);

}
