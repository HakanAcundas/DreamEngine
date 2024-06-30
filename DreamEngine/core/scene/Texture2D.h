#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace dream { namespace graphics {

	class Texture2D
	{
	public:
		class SubTexture2D
		{
		public:
			SubTexture2D(Texture2D* texture, const glm::vec2& min, const glm::vec2& max)
				: m_Texture(texture)
			{
				m_TexCoords[0] = { min.x, min.y };
				m_TexCoords[1] = { max.x, min.y };
				m_TexCoords[2] = { max.x, max.y };
				m_TexCoords[3] = { min.x, max.y };
			}

			Texture2D* GetTexture() const { return m_Texture; }
			const glm::vec2* GetTexCoords() const { return m_TexCoords; }
		private:
			Texture2D* m_Texture;
			glm::vec2 m_TexCoords[4];
		};

	private:
		std::string m_Path;
		unsigned int m_Width, m_Height;
		unsigned int  m_TID;
	public:
		Texture2D(std::string path);
		~Texture2D();

		void SetData(void* data, unsigned int size);
		void Bind() const;
		void Unbind() const;

		static SubTexture2D* CreateSubTexture2D(Texture2D* texture, const glm::vec2 coords, const glm::vec2 spriteSize)
		{
			glm::vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight()};
			glm::vec2 max = { ((coords.x + 1) * spriteSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y) / texture->GetHeight()};
			return new SubTexture2D(texture, min, max);
		}

		const std::string GetPath() const { return m_Path; }
		unsigned int GetHeight() const { return m_Height; }
		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetTID() const { return m_TID; }
	};
}}