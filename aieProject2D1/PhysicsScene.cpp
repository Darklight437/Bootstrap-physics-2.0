#include "PhysicsScene.h"
#include "RigidBody.h"
#include <iostream>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}


void PhysicsScene::update(float deltatime)
{

	static std::list<PhysicsObject*> dirty;

	//update physics at a fixed timestep

	static float accumulatedTime = 0.0f;
	accumulatedTime += deltatime;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor: m_actors)
		{
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		//check for collisions (ideally you'd want to have some sort of scene manager in place
		for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{
				if (pActor == pOther)
				{
					continue;
				}
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() && 
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
				{
					continue;
				}
				RigidBody* pRigid = dynamic_cast<RigidBody*> (pActor);
				if (pRigid->checkCollision(pOther) == true)
				{
					pRigid->applyForceToActor(dynamic_cast<RigidBody*>(pOther), pRigid->getVelocity() * pRigid->getMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}
		dirty.clear();
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
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << ":";
	}
}



PhysicsScene::~PhysicsScene()
{
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
}

void PhysicsScene::removeActor(PhysicsObject * actor)
{
}
