#include "Fonts.hpp"

#include <exception>

namespace ftlib {
    FT_Library ft;
}

////////////
// Font
////////////

Font::Font(const char* fontPath, int size) {
    std::string path = std::string(fontPath);

    FT_New_Face(ftlib::ft, (path + "bold.ttf").c_str(), 0, &bold);
    FT_New_Face(ftlib::ft, (path + "italic.ttf").c_str(), 0, &italic);
    FT_New_Face(ftlib::ft, (path + "light.ttf").c_str(), 0, &light);
    FT_New_Face(ftlib::ft, (path + "regular.ttf").c_str(), 0, &regular);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_Set_Pixel_Sizes(bold, size, 0);
    FT_Set_Pixel_Sizes(italic, size, 0);
    FT_Set_Pixel_Sizes(light, size, 0);
    FT_Set_Pixel_Sizes(regular, size, 0);

    boldChars = load(bold);
    italicChars = load(italic);
    lightChars = load(light);
    regularChars = load(regular);
}

Character charCreator(FT_Face face, unsigned char c) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
        throw "Invalid Character or Face";
    }

    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character = {
        texture, 
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
    };

    glBindTexture(GL_TEXTURE_2D, 0);

    return character;
}

std::map<char, Character> Font::load(FT_Face face) {
    std::map<char, Character> chars;

    Character cc;

    for (unsigned char c = 0; c < 128; c++) {
        try {
            cc = charCreator(face, c);
        } catch(const char* msg) {
            continue;
        }

        chars.insert(std::pair<char, Character>(c, cc));
    }

    return chars;
}

std::map<char, Character> Font::getChars() {
    switch (mode) {
        case REGULAR:
            return regularChars;

        case BOLD:
            return boldChars;

        case ITALIC:
            return italicChars;

        case LIGHT:
            return lightChars;
        
        default:
            return regularChars;
    }
}

void Font::changeSize(int size) {
    this->size = size;

    FT_Set_Pixel_Sizes(bold, 0, size);
    FT_Set_Pixel_Sizes(italic, 0, size);
    FT_Set_Pixel_Sizes(light, 0, size);
    FT_Set_Pixel_Sizes(regular, 0, size);
}

void Font::changeMode(FontMode mode) {
    this->mode = mode;
}

void Font::getTextSize(std::string text, float &width, float &height, float scale) {
    std::map<char, Character> chars = getChars();

    float w = 0;

    float xOffset = chars[text.at(0)].bearing.x * scale + chars[text.at(text.size()-1)].bearing.x * scale;

    for (int i = 0; i < text.size(); i++) {
        Character c = chars[text.at(i)];

        w += (c.advance >> 6) * scale;
    }

    width = w - xOffset;
    height = chars[text.at(0)].size.y * scale;
}

const char* Font::getFontPath() {
    return fontPath;
}

int Font::getSize() {
    return size;
}

FontMode Font::getMode() {
    return mode;
}

////////////////
// Fonts
///////////////
bool fonts::init() {
    return FT_Init_FreeType(&ftlib::ft);
}

Font* fonts::open_sans;