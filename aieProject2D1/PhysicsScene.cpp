#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include "box.h"
#include "OBB.h"
#include <glm\ext.hpp>
#include <iostream>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
	
}


typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::Plane2Plane,  PhysicsScene::Plane2Sphere, PhysicsScene::Plane2AABB,
	PhysicsScene::Sphere2Plane, PhysicsScene::Sphere2Sphere, PhysicsScene::Sphere2AABB,
	PhysicsScene::AABB2Plane, PhysicsScene::AABB2Sphere, PhysicsScene::AABB2AABB,
	PhysicsScene::OOB2Plane
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

bool PhysicsScene::Plane2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	PhysicsObject* newObj1 = obj2;
	PhysicsObject* newObj2 = obj1;
	AABB2Plane(newObj1, newObj2);
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
			glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
			plane->resolveCollision(sphere, contact);
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
			
			sphere1->resolveCollision(sphere2 , 0.5f * (sphere1->getPosition() + sphere2->getPosition()), nullptr);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::Sphere2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	PhysicsObject* new1;
	PhysicsObject* new2;


	return false;
}

bool PhysicsScene::AABB2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
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

bool PhysicsScene::AABB2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
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
				sphere->applyForce(-sphere->getVelocity(), collisionPoint);
				return true;
			}
			return false;
		}
		
	}
	return false;
}

bool PhysicsScene::AABB2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
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

bool PhysicsScene::OOB2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	OBB * box = dynamic_cast<OBB*>(obj1);
	Plane * plane = dynamic_cast<Plane*>(obj2);

	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;
		float radius = 0.5f * std::fminf(box->getWidth(), box->getHeight());

		// which side is the centre of mass on?
		glm::vec2 planeOrigin = plane->getNormal() * plane->getDistance();
		float comFromPlane = glm::dot(box->getPosition() - planeOrigin, plane->getNormal());
		// check all four corners to see if we've hit the plane
		for (float x = -box->getMaxDimentions().x; x<box->getWidth(); x += box->getWidth()) 
		{
			for (float y = -box->getMaxDimentions().y; y<box->getHeight(); y += box->getHeight()) 
			{
				// get the position of the corner in world space
				glm::vec2 p = box->getPosition() + x * box->getLocalX() +
					y * box->getLocalY();
				float distFromPlane = glm::dot(p - planeOrigin, plane->getNormal());

				// this is the total velocity of the point
				float velocityIntoPlane = glm::dot(box->getVelocity() + box->getRotation() *
					(-y * box->getLocalX() + x * box->getLocalY()), plane->getNormal());


				// if this corner is on the opposite side from the COM,
				// and moving further in, we need to resolve the collision
				if ((distFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0) ||
					(distFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane < 0)) 
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}
		// we've had a hit - typically only two corners can contact
		if (numContacts > 0) 
		{
			// get the average collision velocity into the plane
			// (covers linear and rotational velocity of all corners involved)
			float collisionV = contactV / (float)numContacts;
			// get the acceleration required to stop (restitution = 0) or reverse
			// (restitution = 1) the average velocity into the plane
			glm::vec2 acceleration = -plane->getNormal() *
				((1.0f + box->getElasticity()) * collisionV);
			// and the average position at which we'll apply the force
			// (corner or edge centre)
			glm::vec2 localContact = (contact / (float)numContacts) - box->getPosition();
			// this is the perpendicular distance we apply the force at relative to
			// the COM, so Torque = F*r
			float r = glm::dot(localContact, glm::vec2(plane->getNormal().y,
				-plane->getNormal().x));
			// work out the "effective mass" - this is a combination of moment of
			// inertia and mass, and tells us how much the contact point velocity
			// will change with the force we're applying
			float mass0 = 1.0f / (1.0f / box->getMass() + (r*r) / box->getMoment());


	}


	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Collision functions/END
////////////////////////////////////////////////////////////////////////////////////////////////


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
