#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glad/glad.h>

#include <vector>

#include <string>

class Shader {
    public:
        Shader(const char* source, GLenum type);

        bool compile();

        const char* getSource();
        
        GLenum getType();

        unsigned int getId();

    private:
        const char* source;

        unsigned int id;

        GLenum type;
};

class Program {
    public:
        bool init(std::string vertex, std::string fragment);

        void attachShaders();
        void detachShaders();
        void compileShaders();

        void createShader(const char* source, GLenum type);

        void use();

        unsigned int getUniform(const char* name);
        unsigned int getAttrib(const char* name);
        unsigned int getId();

        const char* getGLSLversion();

    private:
        unsigned int id;

        std::vector<Shader *> shaderList;
};

namespace programs {
    extern Program* object;
    extern Program* text;
}

#endif