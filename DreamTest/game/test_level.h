#pragma once
#include <vector>
#include "window.h"
#include "entities/player.h"

using namespace dream;
using namespace graphics;

class TestLevel
{
private:
	std::vector<Player*> m_walls;
	std::vector<Player*> m_enemies;
	Player *m_player;
	bool m_running = true;
	bool m_minimized = false;
	float m_last_frame_time = 0.0f;
	float r = 0;
public:
	TestLevel();
	~TestLevel();

	void run();
	std::vector<Player*> get_walls() { return m_walls; }
	std::vector<Player*> get_enemies() { return m_enemies; }
	Player* get_player() { return m_player; }
};
