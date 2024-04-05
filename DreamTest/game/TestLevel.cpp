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

		/*new Texture2D("assets/test1.png"),
		new Texture2D("assets/test2.png"),
		new Texture2D("assets/test3.png"),
		new Texture2D("assets/test4.png"),
		new Texture2D("assets/test7.png")*/
	};

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			m_Renderables.push_back(new Renderable(glm::vec3(x, y, 1), glm::vec2(0.9f, 0.9f), textures[rand() % 5]));
		}
	}
	m_Renderables.push_back(new Renderable(glm::vec3(-10, -3, 1), glm::vec2(6.0f, 6.0f), textures[1]));
	m_Renderables.push_back(new Renderable(glm::vec3(10, 3, 1), glm::vec2(6.0f, 6.0f), textures[2]));
}
