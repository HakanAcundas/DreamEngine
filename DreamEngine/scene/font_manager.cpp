#include "font_manager.h"
#include <iostream>

namespace dream { namespace graphics {

    // Definition of the static member variable
    std::unordered_map<std::string, TextureLabel*> FontManager::font_cache;

    TextureLabel* FontManager::get_font(const std::string& font_path)
    {
        // Check if the font is already cached
        if (font_cache.find(font_path) == font_cache.end())
        {
            try
            {
                font_cache[font_path] = new TextureLabel(font_path);
            } 
            catch (const std::exception& e)
            {
                std::cerr << "Failed to load font: " << font_path << ". Error: " << e.what() << std::endl;
                return nullptr;
            }
        }
        return font_cache[font_path];
    }

    void FontManager::cleanup()
    {
        // Delete all cached fonts and clear the cache
        for (auto& pair : font_cache)
        {
            delete pair.second;
        }
        font_cache.clear();
    }

}}
