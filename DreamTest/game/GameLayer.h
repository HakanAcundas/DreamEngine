#pragma once
#include "graphics/scene/layers/Layer.h"

namespace dream {
	namespace graphics {

		class GameLayer : public Layer
		{
		private:
			Shader* m_Shader;
			glm::mat4 m_ProjectionMatrix;
			Camera* m_Camera;
		public:
			GameLayer(Shader* shader);
			GameLayer(Shader* shader, Camera* camera);
			~GameLayer();

			void OnUpdate();
			void Render();
			void SetCamera(Camera* camera) { m_Camera = camera; }
			Shader* GetShader() { return m_Shader; }
		};
	}
}