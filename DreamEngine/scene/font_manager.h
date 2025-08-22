#pragma once

#include <unordered_map>
#include <string>
#include "texture_label.h"

namespace dream { namespace graphics {

    class FontManager
    {
    private:
        static std::unordered_map<std::string, TextureLabel*> font_cache;

    public:
        static TextureLabel* get_font(const std::string& font_path);
        static void cleanup();
    };

}}
