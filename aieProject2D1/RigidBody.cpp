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
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timestep;
	

}

void RigidBody::debug()
{
}

void RigidBody::applyForce(glm::vec2 force)
{
	m_velocity += (force / m_mass);
	
	//if (length(m_velocity) < MIN_LINEAR_THRESHOLD) 
	//{
	//	m_velocity = vec2(0, 0);
	//}
	//if (abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD) 
	//{
	//	m_angularVelocity = 0;
	//}
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
	//confirm if objects are moving towards eachother


	float elasticity = (m_elasticity + actor2->getElasticity()) * 0.5f;
	
	float j = glm::dot(-(1 + elasticity) * (relativeVeclocity), normal) /
		glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;

	applyForceToActor(actor2, force);

}
