#include "texture_label.h"
#include <glad/glad.h>
#include <iostream>

namespace dream { namespace graphics {

TextureLabel::TextureLabel(const std::string& font_path) 
    : m_font_path(font_path), m_tid(0) {
    if (FT_Init_FreeType(&m_ft)) {
        std::cerr << "ERROR::FREETYPE: Could not initialize FreeType Library" << std::endl;
        return;
    }
    load_font(font_path);
}

TextureLabel::~TextureLabel() {
    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);

    for (const auto& pair : m_characters) {
        glDeleteTextures(1, &pair.second.c_texture_id);
    }
}

void TextureLabel::load_font(const std::string& font_path) {
    if (FT_New_Face(m_ft, font_path.c_str(), 0, &m_face)) {
        std::cerr << "ERROR::FREETYPE: Failed to load font " << font_path << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(m_face, 0, 48); // Set font size
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR::FREETYPE: Failed to load Glyph " << c << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED, // Internal format for grayscale
            m_face->glyph->bitmap.width,
            m_face->glyph->bitmap.rows,
            0,
            GL_RED, // Format for grayscale
            GL_UNSIGNED_BYTE,
            m_face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
            glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
            static_cast<unsigned int>(m_face->glyph->advance.x)
        };
        m_characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

}}
