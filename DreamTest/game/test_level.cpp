#include "test_level.h"

using namespace dream;
using namespace graphics;

TestLevel::TestLevel()
{
	run();
}

TestLevel::~TestLevel()
{

}

void TestLevel::run()
{
	Texture2D *atlasTexture = new Texture2D("../DreamTest/assets/Main Characters/Virtual Guy/Double Jump (32x32).png");
	Texture2D::SubTexture2D* mySubTex = Texture2D::create_sub_texture_2d(atlasTexture, glm::vec2(1, 0), glm::vec2(32,32));
	m_player = new Player(glm::vec3(2, 2, 1), glm::vec2(2.0f, 2.0f), mySubTex);
}
