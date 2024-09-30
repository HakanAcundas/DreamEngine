#pragma once
#include <vector>
#include "window.h"
#include "entity.h"

using namespace dream;
using namespace graphics;

class TestLevel
{
private:
	std::vector<Entity*> m_Walls;
	std::vector<Entity*> m_Enemies;
	Entity* m_Player;
	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;
	float r = 0;
public:
	TestLevel();
	~TestLevel();

	void Run();
	std::vector<Entity*> GetWalls() { return m_Walls; }
	std::vector<Entity*> GetEnemies() { return m_Enemies; }
	Entity* GetPlayer() { return m_Player; }
};
