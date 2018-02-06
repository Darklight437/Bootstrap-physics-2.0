#include "RigidBody.h"





RigidBody::RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : PhysicsObject(shapeID)
{

}


RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timestep)
{
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
}
