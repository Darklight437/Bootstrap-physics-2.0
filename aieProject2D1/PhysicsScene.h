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
	PhysicsObject* getLastActor();
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
	static bool Plane2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Plane2AABB(PhysicsObject*, PhysicsObject*);
	static bool Sphere2Plane(PhysicsObject*, PhysicsObject*);
	static bool Sphere2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Poly2Plane(PhysicsObject*, PhysicsObject*);
	static bool Plane2Poly(PhysicsObject*, PhysicsObject*);
	static bool Poly2Sphere(PhysicsObject*, PhysicsObject*);
	static bool Sphere2Poly(PhysicsObject*, PhysicsObject*);
	static bool Poly2Poly(PhysicsObject*, PhysicsObject*);
	static bool Sphere2AABB(PhysicsObject*, PhysicsObject*);
	static bool AABB2Plane(PhysicsObject*, PhysicsObject*);
	static bool AABB2Sphere(PhysicsObject*, PhysicsObject*);
	static bool AABB2AABB(PhysicsObject*, PhysicsObject*);
	static bool OOB2Plane(PhysicsObject*, PhysicsObject*);
	//Collisions end

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
	
};

