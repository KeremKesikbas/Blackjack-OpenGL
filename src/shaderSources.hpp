#ifndef SHADERSOURCES_HPP
#define SHADERSOURCES_HPP

#include <string>

// Vertex Shader source

const std::string o_vertex_source = 
    "#version 330 core \n"

    "layout (location = 0) in vec2 inPosition; \n"
    "layout (location = 1) in vec2 inTextureCoors; \n"

    "uniform mat3 translate; \n"
    "uniform mat3 angle; \n"
    "uniform mat3 scale; \n"

    "out vec2 textureCoors; \n"

    "void main() { \n"
    "   gl_Position = vec4(translate * angle * scale * vec3(inPosition, 1.0), 1.0); \n"

    "   textureCoors = inTextureCoors; \n"
    "} \n";

// Fragment Shader Source

const std::string o_fragment_source = 
    "#version 330 core \n"

    "uniform vec4 color; \n"
    "uniform int mode; \n"

    "out vec4 outColor; \n"

    "in vec2 textureCoors; \n"

    "uniform sampler2D tex0; \n"

    "void main() { \n"
    "   if (mode == 2) { \n"
            "outColor = color * texture(tex0, textureCoors); \n"
        "} \n"

        "else if (mode == 0) { \n"
            "outColor = color; \n"
        "} \n"

        "else if (mode == 1) { \n"
            "outColor = texture(tex0, textureCoors); \n"
        "} \n"
    "} \n";

const std::string t_vertex_source = 
    "#version 330 core \n"

    "layout (location = 0) in vec4 vertex; \n"

    "out vec2 TexCoords; \n"

    "uniform mat4 projection; \n"

    "void main() { \n"
        "gl_Position = projection * vec4(vertex.x, vertex.y, 0.0, 1.0); \n"
        "TexCoords = vec2(vertex.z, vertex.w); \n"
    "} \n";

const std::string t_fragment_source = 
    "#version 330 core \n"
    
    "in vec2 TexCoords; \n"
    "out vec4 color; \n"

    "uniform sampler2D text; \n"
    "uniform vec4 textColor; \n"

    "void main() { \n"
        "color = textColor * vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r); \n"
    "} \n";

#endif