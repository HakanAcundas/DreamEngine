#pragma once
#include <vector>
#include <window.h>
#include <entity.h>

using namespace dream;
using namespace graphics;

class TestLevel
{
private:
	std::vector<Entity*> m_walls;
	std::vector<Entity*> m_enemies;
	Entity *m_player;
	bool m_running = true;
	bool m_minimized = false;
	float m_last_frame_time = 0.0f;
	float r = 0;
public:
	TestLevel();
	~TestLevel();

	void run();
	std::vector<Entity*> get_walls() { return m_walls; }
	std::vector<Entity*> get_enemies() { return m_enemies; }
	Entity* get_player() { return m_player; }
};
