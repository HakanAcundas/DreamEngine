#pragma once
#include <string>
#include <GL/glew.h>

namespace dream { namespace graphics {

	class Texture2D
	{
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		bool m_IsLoaded = false;
	public:
		Texture2D(std::string path);
		~Texture2D();

		void Bind(uint32_t slot) const;

		const std::string GetPath() const { return m_Path; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetRendererID() const { return m_RendererID; }
		bool IsLoaded() const { return m_IsLoaded; }
	};
}}