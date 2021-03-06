#include "aieProject2D1App.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "OBB.h"
#include <glm/ext.hpp>
#include <Gizmos.h>
#include "Polygon.h"



aieProject2D1App::aieProject2D1App() 
{

}

aieProject2D1App::~aieProject2D1App() 
{

}

bool aieProject2D1App::startup() 
{
	
	//increase the 2d line count to maximise the number of objects drawable
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_PhysicsScene = new PhysicsScene();
	m_PhysicsScene->setGravity(glm::vec2(0, -9.8));
	m_PhysicsScene->setTimeStep(0.01f);

	//add planes
	m_PhysicsScene->addActor(new Plane(glm::vec2(20, 10), -45.0f));
	m_PhysicsScene->addActor(new Plane(glm::vec2(-20, 10), -45.0f));
	m_PhysicsScene->addActor(new Plane(glm::vec2(0, 1), -40.0f));
	m_PhysicsScene->addActor(new Plane(glm::vec2(0, 1), 40.0f));


	//add shapes
	                                                                    
	//for (int i = 0; i < 10; i++)
	//{
	//	m_PhysicsScene->addActor(new Sphere(glm::vec2(40 - i * 5, 5), glm::vec2(-25, 1), 1.0f, 2.0f, 0.0f, glm::vec4(0, 1, 0, 1)));
	//}


	m_PhysicsScene->addActor(new Box(glm::vec2(10, 3), glm::vec2(0), glm::vec2(3, 5), 1.0f, glm::vec4(0, 0, 1, 1)));
	
	//m_PhysicsScene->addActor(new Polygon(glm::vec2(20, 10), glm::vec2(0, -9.8), 1.0f, 5.0f, 7, glm::vec4(1, 0, 0, 1)));
	m_PhysicsScene->addActor(new Sphere(glm::vec2(10, 10), glm::vec2(0, 9.8), 1.0f, 2.0f, glm::vec4(1, 0, 0, 1)));

	
	

	


	return true;
}


//uses kinematic formulae to accurately simulate physics (does not work in real time)
void aieProject2D1App::setupContinuousDemo(glm::vec2 startpos, float inclination, float speed, float gravity)
{
	float t = 0;
	float tstep = 0.1f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);

	

	while (t <= 5)
	{
		//calculate the x, y position of the projectile at time t
		float x = 0;
		float y = 0;
		x = startpos.x + speed * t;
		y = startpos.y + (speed* t) + gravity / 2 * (t *t);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);

		t += tstep;
	}
}


void aieProject2D1App::shutdown() 
{
	delete m_font;
	delete m_2dRenderer;
}

void aieProject2D1App::update(float deltaTime) 
{

	// input example
	aie::Input* input = aie::Input::getInstance();
	if (input->wasMouseButtonPressed(0))
	{
		m_PhysicsScene->addActor(new Sphere(glm::vec2(10, 10), glm::vec2(0, 9.8), 1.0f, 2.0f, 0.0f, glm::vec4(1, 0, 0, 1)));
	} 
	if (input->wasMouseButtonPressed(1))
	{
		if (m_PhysicsScene->getLastActor()->getShapeID() != shapeType::PLANE)
		{
			m_PhysicsScene->removeActor(m_PhysicsScene->getLastActor());
		}
		
	}

	aie::Gizmos::clear();
	
	m_PhysicsScene->update(deltaTime);
	m_PhysicsScene->updateGizmos();



	//m_PhysicsScene->debugScene();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void aieProject2D1App::draw() 
{

	// wipe the screen to the background colour
	clearScreen();
	
	// begin drawing sprites
	m_2dRenderer->begin();
	
	
	// draw your stuff here!


	//gizmo orthographic grid (draws gizmos too)
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}



