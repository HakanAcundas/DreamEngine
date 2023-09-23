#pragma once
#include "../buffers/VertexArray.h"
#include "../Shader.h"
#include "../Texture2D.h"
#include "../Camera.h"
#include "../Renderable.h"


namespace dream { namespace graphics {

	//Data that goes into Shader
	struct RenderableData
	{
		glm::vec3 Position;
		unsigned int Color;
		glm::vec2 TexCoord;
		float TextureID;
	};

	class Renderer2D
	{
	private:
		static Buffer* m_Buffer;
		static VertexArray* m_VertexArray;
		static IndexBuffer* m_IndexBuffer;
		GLsizei m_IndexCount;
		std::vector<Renderable*> m_Renderables;
		std::vector<unsigned int> m_TextureSlots;

		RenderableData* m_RenderableData;
	public:
		static void Init();
		static void Shutdown();

		void End();
		void Begin();
		void AddRenderable(Renderable* renderable);
		void RemoveRenderable(Renderable* renderable);
		void Render();
		void Flush();


		// Primitives
		//void DrawRenderable(const Renderable* renderable);
		//static void DrawRenderable(const glm::vec2& position, const glm::vec2& size, const Texture2D* texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};
}}