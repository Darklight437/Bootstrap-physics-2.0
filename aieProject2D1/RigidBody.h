#pragma once
#include "PhysicsObject.h"
#include <glm/ext.hpp>

#define MIN_LINEAR_THRESHOLD  0.01f
#define MIN_ROTATIONAL_THRESHOLD  0.01f

class RigidBody : public PhysicsObject
{
public:
	RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	RigidBody(shapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass, float elasticity);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timestep);
	virtual void debug();
	void applyForce(glm::vec2 force, glm::vec2 pos);
	void resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal);

	//virtual bool checkCollision(PhysicsObject* pOther) = 0;


	glm::vec2 getPosition() { return m_position; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getRotation() { return m_rotation; }
	float getMomentOfInertia() { return m_moment; }
	float getMass() { return m_mass; }
	float getANDrag() { return m_angularDrag; }
	float getLINDrag() { return m_angularDrag; }
	float getElasticity() { return m_elasticity; }
	float getAngularVelocity() { return m_angularVelocity; }
	void setANDrag(float angularDrag) { m_angularDrag = angularDrag; }
	void setLINDrag(float linearDrag) { m_linearDrag = linearDrag; }
	void setElasticity(float newElasticityCoefficient) { m_elasticity = newElasticityCoefficient; }
	

protected:


	bool isKinematic;
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_angularVelocity;
	float m_moment;
	float m_mass;
	float m_rotation; //2D so we only need a single float to represent our rotation
	float m_elasticity = 1;
	float m_linearDrag = 0.3f;
	float m_angularDrag = 0.3f;



};
