#pragma once
#include "Layer.h"
#include "TestLevel.h"

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
private:
	Shader* m_Shader;
	glm::mat4 m_ProjectionMatrix;
	Camera* m_Camera;
	glm::vec2 m_LightPos;
	TestLevel m_Level;
	unsigned int currentLevel = 0;
public:
	GameLayer(Shader* shader);
	GameLayer(Shader* shader, Camera* camera);

	GameLayer(std::string& vertexShader, std::string& fragmentShader, Camera* camera);
	~GameLayer();

	void OnUpdate() override;
	void OnEvent(Event& e) override;
	bool OnKeyPressed(KeyPressedEvent& e);
	bool OnMouseMoved(MouseMovedEvent& e);
	void SetCamera(Camera* camera) { m_Camera = camera; }
	Shader* GetShader() { return m_Shader; }
};
