#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include "box.h"
#include <glm\ext.hpp>
#include <iostream>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
	
}


typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::Plane2Plane,  PhysicsScene::Plane2Sphere, PhysicsScene::Plane2Box,
	PhysicsScene::Sphere2Plane, PhysicsScene::Sphere2Sphere, PhysicsScene::Sphere2Box,
	PhysicsScene::Box2Plane, PhysicsScene::Box2Sphere, PhysicsScene::Box2Box
};

void PhysicsScene::update(float deltatime)
{

	

	//update physics at a fixed timestep

	static float accumulatedTime = 0.0f;
	accumulatedTime += deltatime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor: m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		//check for collisions (ideally you'd want to have some sort of scene manager in place
		//to determine whether a collision check is necessary

		checkForCollision();

		
		
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors )
	{
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	/*int count = 0;
	for (auto pActor : m_actors)
	{
		count++;
	}
	std::cout << count << ":";*/
}

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();
	//checking against all objects for collisions except this one

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();

			//using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr!= nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Collision functions
////////////////////////////////////////////////////////////////////////////////////////////////

bool PhysicsScene::Plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	PhysicsObject* new1 = obj2;
	PhysicsObject* new2 = obj1;
	Sphere2Plane(new1, new2);
	//hopefully
	return true;
}

bool PhysicsScene::Plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	PhysicsObject* newObj1 = obj2;
	PhysicsObject* newObj2 = obj1;
	Box2Plane(newObj1, newObj2);
	return true;
}

bool PhysicsScene::Sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere *sphere = dynamic_cast<Sphere*>(obj1);
	Plane * plane = dynamic_cast<Plane*>(obj2);

	//if the casts are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();

		//if we are behind the plane
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0)
		{
			sphere->applyForce(-sphere->getVelocity());
		}
	}


	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//cast objects to type shpere
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	//test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{

		//if spheres are overlapping
		if (glm::distance(sphere1->getPosition(),sphere2->getPosition()) <= (sphere1->getRadius() + sphere2->getRadius()))
		{
			sphere1->applyForce(-sphere1->getVelocity());
			sphere2->applyForce(-sphere2->getVelocity());
			return true;
		}
	}
	return false;
}

bool PhysicsScene::Box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box *box = dynamic_cast<Box*>(obj1);
	Plane * plane = dynamic_cast<Plane*>(obj2);

	if (box != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();

		float corner1Dot = glm::dot(box->getCorner(1), plane->getNormal()) - plane->getDistance();
		float corner2Dot = glm::dot(box->getCorner(2), plane->getNormal()) - plane->getDistance();
		float corner3Dot = glm::dot(box->getCorner(3), plane->getNormal()) - plane->getDistance();
		float corner4Dot = glm::dot(box->getCorner(4), plane->getNormal()) - plane->getDistance();

		if (std::signbit(corner1Dot) != std::signbit(corner4Dot))
		{
			//do collision
			box->applyForce(-box->getVelocity());
			return true;
		}
		if (std::signbit(corner2Dot) != std::signbit(corner3Dot))
		{
			//do collision
			box->applyForce(-box->getVelocity());
			return true;
		}
		
	}


	return false;
}

bool PhysicsScene::Box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box *box = dynamic_cast<Box*>(obj1);
	Sphere *sphere = dynamic_cast<Sphere*>(obj2);

	if (box != nullptr && sphere != nullptr)
	{
		glm::vec2 collisionPoint = (glm::normalize(box->getPosition() - sphere->getPosition())* sphere->getRadius());
		collisionPoint += sphere->getPosition();
		//if collisionpoint is (within box) then collision has occurred
		//left of boxright & right of boxleft
		//up of boxdown & down of boxup
		bool test1 = ((box->getCorner(1).x < collisionPoint.x) && (box->getCorner(2).x > collisionPoint.x));
		bool test2 = (box->getCorner(1).y > collisionPoint.y && box->getCorner(3).y < collisionPoint.y);
		if (test1 == true)
		{
			if (test2 == true)
			{
				
				box->applyForce(-box->getVelocity());
				sphere->applyForce(-sphere->getVelocity());
				return true;
			}
			return false;
		}
		
	}
	return false;
}

bool PhysicsScene::Box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//cast objects to type Box
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	//test for collision
	//bool test1 = box1->getPosition().x - box1->getDimentions().x / 2 < 
	
	bool test1 = (box1->getCorner(4).x < box2->getCorner(1).x);
	bool test2 = (box2->getCorner(4).x < box1->getCorner(1).x);
	bool test3 = (box1->getCorner(4).y > box2->getCorner(1).y);
	bool test4 = (box2->getCorner(4).y > box1->getCorner(1).y);

	if (!(test1 || test2 || test3 || test4))
	{
		
		box1->applyForce(-box1->getVelocity());
		box2->applyForce(-box2->getVelocity());
		return true;
	}


	return false;
}



PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject * actor)
{
	m_actors.erase(std::find(m_actors.begin(), m_actors.end(), actor));
	
}
