#pragma once
#include <vector>
#include "core/window/Window.h"
#include "core/scene/Renderable.h"

using namespace dream;
using namespace graphics;

class TestLevel
{
private:
	std::vector<Renderable*> m_Renderables;
	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;
	float r = 0;
public:
	TestLevel();
	~TestLevel();

	void Run();
	std::vector<Renderable*> GetRenderables() { return m_Renderables; }
};
