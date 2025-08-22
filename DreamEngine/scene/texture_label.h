#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace dream { namespace graphics {

class TextureLabel {
public:
    struct Character {
        unsigned int c_texture_id;  // Texture ID storing character glyph
        glm::ivec2 c_size;          // Size of the glyph
        glm::ivec2 c_bearing;       // Offset from baseline to top-left corner
        unsigned int c_advance;     // Horizontal offset to next glyph
    };

private:
    std::map<char, Character> m_characters;  // Character map
    unsigned int m_tid;                      // Texture ID
    FT_Library m_ft;                         // FreeType library
    FT_Face m_face;                          // FreeType face
    std::string m_font_path;                 // Path to font file

public:
    TextureLabel(const std::string& font_path);
    ~TextureLabel();

    void load_font(const std::string& font_path);
    const std::map<char, Character>& get_characters() const { return m_characters; }
};

}}
