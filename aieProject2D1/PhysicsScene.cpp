#include "PhysicsScene.h"



PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}


void PhysicsScene::update(float deltatime)
{
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
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors )
	{
		pActor->makeGizmo();
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
