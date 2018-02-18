#pragma once
#include "PhysicsObject.h"
#include <glm/ext.hpp>
class RigidBody : public PhysicsObject
{
public:
	RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float elasticity);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timestep);
	virtual void debug();
	void applyForce(glm::vec2 force);
	void applyForceToActor(RigidBody* actor2, glm::vec2 force);
	void resolveCollision(RigidBody* actor2);

	//virtual bool checkCollision(PhysicsObject* pOther) = 0;


	glm::vec2 getPosition() { return m_position; }
	float getRotation() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	void setElasticity(float newElasticityCoefficient) { m_elasticity = newElasticityCoefficient; }

protected:


	bool isKinematic;
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	float m_rotation; //2D so we only need a single float to represent our rotation
	float m_elasticity = 1;
};
