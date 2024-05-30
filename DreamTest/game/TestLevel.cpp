#pragma once
#include "TestLevel.h"


using namespace dream;
using namespace graphics;

TestLevel::TestLevel()
{
	Run();
}

TestLevel::~TestLevel()
{

}

void TestLevel::Run()
{
	Texture2D* textures[] =
	{
		new Texture2D("assets/Background/Blue.png"),
		new Texture2D("assets/Background/Brown.png"),
		new Texture2D("assets/Background/Gray.png"),
		new Texture2D("assets/Background/Green.png"),
		new Texture2D("assets/Background/Pink.png")
	};

	for (float y = 0.0f; y < 9.0f; y+=0.5)
	{
		for (float x = 0.0f; x < 16.0f; x+=0.5)
		{
			m_Renderables.push_back(new Renderable(glm::vec3(x, y, 1), glm::vec2(0.4f, 0.4f), textures[rand() % 5]));
		}
	}
	m_Renderables.push_back(new Renderable(glm::vec3(-10, -3, 1), glm::vec2(2.0f, 2.0f), textures[1]));
	m_Renderables.push_back(new Renderable(glm::vec3(10, 3, 1), glm::vec2(2.0f, 2.0f), textures[2]));
}
