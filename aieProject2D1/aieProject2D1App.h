#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"

class aieProject2D1App : public aie::Application {
public:

	aieProject2D1App();
	virtual ~aieProject2D1App();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void setupContinuousDemo(glm::vec2 startpos, float inclination, float speed, float gravity);
protected:

	PhysicsScene* m_PhysicsScene;
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
};