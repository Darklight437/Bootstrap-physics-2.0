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
	m_PhysicsScene->setGravity(glm::vec2(0, 0));
	m_PhysicsScene->setTimeStep(0.01f);
	
	Sphere* ball;
	RigidBody* rb;
	//rb = new RigidBody();
	rb = new Sphere(glm::vec2(-40, 0), glm::vec2(10, 30), 3.0f, 1, glm::vec4(1, 0, 0, 1));

	return true;
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
	
	
	m_PhysicsScene->update(deltaTime);
	m_PhysicsScene->updateGizmos();



	

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
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}