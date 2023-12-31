#pragma once
#include <cstddef>
#include <map>
#include "../buffers/VertexArray.h"
#include "../scene/Shader.h"
#include "../scene/Camera.h"
#include "../scene/Renderable.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace dream { namespace graphics {

#define RENDERER_MAX_RENDERABLE	20000
#define RENDERER_VERTEX_SIZE	sizeof(RenderableData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4 
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_RENDERABLE
#define RENDERER_INDICES_SIZE	RENDERER_MAX_RENDERABLE * 6

	typedef struct {
		unsigned int	c_TextureID;	// texture id storing character
		glm::ivec2		c_Size;			// size of char
		glm::ivec2		c_Bearing;		// distance from origin to top left of char
		unsigned int	c_Advance;		// distance from origin to next origin (1/64th pixels)
	} Character;

	struct RenderableData
	{
		glm::vec3 position;
		glm::vec2 textureCoord;
		float textureID;
		glm::vec4 color;
	};

	struct RendererData
	{
		Buffer* buffer;
		VertexArray* vertexArray;
		IndexBuffer* indexBuffer;
		std::vector<unsigned int> textureSlots;
		std::map<char, Character> characters;

		RenderableData* renderableData = nullptr;
		uint32_t renderableIndexCount;
		glm::vec4 renderableVertexPositions[4];
		glm::vec2 textureCoords[4];

		struct CameraData
		{
			glm::mat4 viewProjection;
		};
		CameraData cameraBuffer;
	};

	class Renderer2D
	{
	private:
		static Renderer2D *singleton;
		Renderer2D();
		float SubmitTexture(const Texture2D* texture);
	public:
		static Renderer2D* GetSingleton() { return singleton; }

		Renderer2D(const Renderer2D* obj) = delete;
		void Init();
		void Begin();
		void End();
		void DrawRenderable(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		void DrawRenderable(const glm::vec2& position, const glm::vec2& size, const Texture2D* texture, const glm::vec4& color);
		void DrawLabel(const std::string& text, float x, float y, const glm::vec4& color);
		void Flush();

	};
}}
