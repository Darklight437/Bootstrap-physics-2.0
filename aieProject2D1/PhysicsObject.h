#pragma once
#include <glm/vec2.hpp>

enum shapeType{ PLANE = 0, CIRCLE, POLY};
static int SHAPE_COUNT = shapeType::BOX + 1;
class PhysicsObject
{

protected:
	PhysicsObject(shapeType a_shapeID) : m_shapeID(a_shapeID) {}
public:
	virtual void fixedUpdate(glm::vec2 gravity, float timestep) =0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {}
	virtual shapeType getShapeID() { return m_shapeID; }
	~PhysicsObject();

protected:
	shapeType m_shapeID;
};

