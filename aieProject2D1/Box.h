#pragma once
#include "RigidBody.h"
class Box :
	public RigidBody
{
public:
	Box(glm::vec2 position, glm::vec2 velocity, glm::vec2 maxDimentions, float mass,
		glm::vec4 colour);
	~Box();

	virtual void makeGizmo();
	
	virtual void fixedUpdate(glm::vec2 gravity, float timestep);
	virtual void applyForce(glm::vec2 force);
	glm::vec2 getCorner(int corner);
	virtual glm::vec2 getPosition() { return m_position; }
	virtual glm::vec2 getVelocity() { return m_velocity; }
	virtual glm::vec2 getDimentions() { return m_dimentions; }
protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_dimentions;
	float m_mass;
	glm::vec4 m_colour;

};

