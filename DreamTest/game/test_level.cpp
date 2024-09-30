#pragma once
#include "test_level.h"


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
		new Texture2D("DreamTest/assets/Background/Blue.png"),
		new Texture2D("DreamTest/assets/Background/Brown.png"),
		new Texture2D("DreamTest/assets/Background/Gray.png"),
		new Texture2D("DreamTest/assets/Background/Green.png"),
		new Texture2D("DreamTest/assets/Background/Pink.png")
	};

	Texture2D* atlasTexture = new Texture2D("DreamTest/assets/Main Characters/Virtual Guy/Double Jump (32x32).png");
	Texture2D::SubTexture2D* mySubTex = Texture2D::CreateSubTexture2D(atlasTexture, glm::vec2(1, 0), glm::vec2(32,32));
	Entity* m_2ndSprite = new Entity(glm::vec3(10, 3, 1), glm::vec2(2.0f, 2.0f), mySubTex);
	m_Enemies.push_back(m_2ndSprite);
	/*for (float y = 0.0f; y < 9.0f; y+=0.5)
	{
		for (float x = 0.0f; x < 16.0f; x+=0.5)
		{
			m_Walls.push_back(new Entity(glm::vec3(x, y, 1), glm::vec2(0.4f, 0.4f), textures[rand() % 5]));
		}
	}*/
	m_Player = new Entity(glm::vec3(0, 0, 1), glm::vec2(1.0f, 1.0f), new Texture2D("DreamTest/assets/Main Characters/Virtual Guy/Jump.png"));
}
