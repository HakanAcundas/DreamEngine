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

#define RENDERER_MAX_RENDERABLE	20000
#define RENDERER_VERTEX_SIZE	sizeof(RenderableData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4 
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_RENDERABLE
#define RENDERER_INDICES_SIZE	RENDERER_MAX_RENDERABLE * 6

	// Renderable data that goes into Shader
	struct RenderableData
	{
		glm::vec3 Position;
		glm::vec2 TextureCoord;
		float TextureID;
		glm::vec4 Color;
	};

	class Renderer2D
	{
	private:
		static Renderer2D *singleton;
		Renderer2D();
	public:
		Renderer2D(const Renderer2D* obj) = delete;
		void Init();
		void Begin();
		void End();
		void DrawRenderable(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		void DrawRenderable(const glm::vec2& position, const glm::vec2& size, const Texture2D* texture, const glm::vec4& color);
		void DrawRenderable(const glm::vec2& position, const glm::vec2& size, const unsigned int tid, const glm::vec4& color);
		void Flush();

		static Renderer2D* GetSingleton() { return singleton; }
	};
}}
