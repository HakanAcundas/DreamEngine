#pragma once
#include "core/scene/Layer.h"
#include "TestLevel.h"

using namespace dream;
using namespace graphics;

class GameLayer : public Layer
{
private:
	Shader* m_Shader;
	glm::mat4 m_ProjectionMatrix;
	Camera* m_Camera;
	TestLevel m_Level;
public:
	GameLayer(Shader* shader);
	GameLayer(Shader* shader, Camera* camera);

	// TODO Also support this initilize way.
	GameLayer(std::string& vertexShader, std::string& fragmentShader, Camera* camera);
	~GameLayer();

	void OnUpdate() override;
	void OnEvent() override;
	void SetCamera(Camera* camera) { m_Camera = camera; }
	Shader* GetShader() { return m_Shader; }
};
