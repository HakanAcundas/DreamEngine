#pragma once
#include "../Texture2D.h"
#include "../Camera.h"
#include "../Renderable.h"


namespace dream { namespace graphics {

	class Renderer2D
	{
	private:
		unsigned int m_VertexArray;
		unsigned int m_Buffer;
		// This buffer not only contains vertices, it also contains colors etc.
		RenderableData* m_RenderableData;
		IndexBuffer* m_IndexBuffer;
		// We don't need to render RENDERER_MAX_SPRITES. This value counts how much sprite we want to render.
		GLsizei m_IndexCount;
		std::vector<unsigned int> m_TextureSlots;
	public:
		static void Init();
		static void Shutdown();

		void End();
		void Begin();
		void Submit(const Renderable* renderable);
		void Flush();


		// Primitives
		void DrawRenderable(const Renderable* renderable);
		//static void DrawRenderable(const glm::vec2& position, const glm::vec2& size, const Texture2D* texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};
}}