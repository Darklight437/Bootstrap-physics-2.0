#include "aieProject2D1App.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include <glm/ext.hpp>
#include <Gizmos.h>



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
	
	
	
	
	//setupContinuousDemo(glm::vec2(-40,0),20, 9.8, -9.8);
	
	//m_PhysicsScene->addActor(new Sphere(glm::vec2(-40, 0), glm::vec2(9.8, 9.8), 1.0f, 1.0f, glm::vec4(0, 0, 1, 1)));

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
	//aie::Gizmos::clear();
	
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


	//gizmo orthographic grid
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	//m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}



