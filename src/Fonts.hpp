#ifndef FONTS_HPP
#define FONTS_HPP

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

enum FontMode {
    BOLD,
    ITALIC,
    LIGHT,
    REGULAR
};

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    long int advance;
};

class Font {
    public:
        Font(const char* fontPath, int size);

        void changeSize(int size);
        void changeMode(FontMode mode);

        const char* getFontPath();
        
        int getSize();

        FontMode getMode();

        std::map<char, Character> getChars();

        void getTextSize(std::string text, float &width, float &height);

    private:
        std::map<char, Character> load(FT_Face face);

        std::map<char, Character> boldChars;
        std::map<char, Character> italicChars;
        std::map<char, Character> lightChars;
        std::map<char, Character> regularChars;

        FT_Face bold;
        FT_Face italic;
        FT_Face light;
        FT_Face regular;

        const char* fontPath;

        FontMode mode = REGULAR;

        int size;
};

namespace fonts {
    bool init();

    extern Font* open_sans;
}

#endif