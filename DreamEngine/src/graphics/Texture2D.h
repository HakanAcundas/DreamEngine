#pragma once
#include <string>
#include <GL/glew.h>

namespace dream { namespace graphics {

	class Texture2D
	{
	private:
		std::string m_Path;
		unsigned int m_Width, m_Height;
		unsigned int  m_TID;
		bool m_IsLoaded = false;
	public:
		Texture2D(std::string path);
		~Texture2D();

		void SetData(void* data, unsigned int size);
		void Bind(uint32_t slot) const;

		const std::string GetPath() const { return m_Path; }
		unsigned int GetHeight() const { return m_Height; }
		unsigned int GetWidth() const { return m_Width; }
		unsigned int TID() const { return m_TID; }
		bool IsLoaded() const { return m_IsLoaded; }
	};
}}