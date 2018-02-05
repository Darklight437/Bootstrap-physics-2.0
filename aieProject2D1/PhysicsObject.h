#pragma once
#include <glm/vec2.hpp>

enum class shapeType{ PLANE = 0, CIRCLE, BOX};

class PhysicsObject
{

protected:
	PhysicsObject(shapeType a_shapeID) : m_shapeID(a_shapeID) {}
public:
	virtual void FixedUpdate(glm::vec2 gravity, float timestep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
	~PhysicsObject();

protected:
	shapeType m_shapeID;
};

