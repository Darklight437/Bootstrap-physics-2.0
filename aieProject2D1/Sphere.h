#pragma once
#include "RigidBody.h"
class Sphere : public RigidBody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, float elasticity, glm::vec4 colour);
	~Sphere();

	virtual void makeGizmo();
	//virtual bool checkCollision(PhysicsObject* pOther);
	//virtual void fixedUpdate(glm::vec2 gravity, float timestep);

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius = 0;
	glm::vec4 m_colour = glm::vec4(0);

};

