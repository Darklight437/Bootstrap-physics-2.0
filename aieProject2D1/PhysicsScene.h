#pragma once
#include <glm/vec2.hpp>
#include <list>
#include "PhysicsObject.h"
#include "vector"
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float deltatime);
	void updateGizmos();
	void debugScene();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void checkForCollision();

	//possible collision types
	static bool Plane2Plane(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Plane2Sphere(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Plane2Box(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Sphere2Plane(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Sphere2Sphere(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Sphere2Box(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Box2Plane(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Box2Sphere(PhysicsObject*, PhysicsObject*) { return false; }
	static bool Box2Box(PhysicsObject*, PhysicsObject*) { return false; }
	

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
	
};

