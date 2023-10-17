#pragma once
#include <cstddef>
#include "../buffers/VertexArray.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../Renderable.h"


namespace dream { namespace graphics {

//static const uint32_t MaxQuads = 20000;
//static const uint32_t MaxVertices = MaxQuads * 4;
//static const uint32_t MaxIndices = MaxQuads * 6;
//static const uint32_t MaxTextureSlots = 32;

#define RENDERER_MAX_RENDERABLE	60000
#define RENDERER_VERTEX_SIZE	sizeof(RenderableData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4 
#define RENDERER_INDICES_SIZE	RENDERER_MAX_RENDERABLE * 6

	// Data that goes into Shader
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
		Buffer* m_Buffer;
		VertexArray* m_VertexArray;
		IndexBuffer* m_IndexBuffer;
		GLsizei m_IndexCount;
		std::vector<Renderable*> m_Renderables;
		std::vector<unsigned int> m_TextureSlots;

		RenderableData* m_RenderableData;
		RenderableData* m_RenderableVertexBufferBase = nullptr;
		RenderableData* m_RenderableVertexBufferPtr = nullptr;
		uint32_t m_RenderableIndexCount = 0;

	public:
		Renderer2D();
		void Init();
		void Shutdown();

		void StartBatch();
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