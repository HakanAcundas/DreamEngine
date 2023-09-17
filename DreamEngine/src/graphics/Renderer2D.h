#pragma once
#include "Texture2D.h"
#include "Camera.h"

namespace dream { namespace graphics {

	class Renderer2D
	{
	private:
		static void StartBatch();
		static void NextBatch();
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		//static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID);
	};
}}