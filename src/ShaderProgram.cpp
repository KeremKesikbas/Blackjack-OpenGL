#include "ShaderProgram.hpp"

// Programs
Program* programs::object;
Program* programs::text;

/////////////////
// Shader
/////////////////

Shader::Shader(const char* source, GLenum type) {
    this->source = source;
    this->type = type;
}

bool Shader::compile() {
    id = glCreateShader(type);

    if (!id) {
        return false;
    }

    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if(status == GL_FALSE) {
        GLint log_length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);

        GLchar log[log_length];

        glGetShaderInfoLog(id, log_length, &log_length, log);

        return false;
    }

    return true;
}

const char* Shader::getSource() {
    return source;
}

GLenum Shader::getType() {
    return type;
}

unsigned int Shader::getId() {
    return id;
}

//////////////////
// Program
//////////////////

#include <iostream>

bool Program::init(std::string vertex, std::string fragment) {
    id = glCreateProgram();

    if (!id) {
        return false;
    }

    createShader(vertex.c_str(), GL_VERTEX_SHADER);
    createShader(fragment.c_str(), GL_FRAGMENT_SHADER);

    compileShaders();
    attachShaders();

    glLinkProgram(id);

    detachShaders();

    GLint status;

    glGetProgramiv(id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        GLint log_length = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length);

        GLchar log[log_length];

        glGetProgramInfoLog(id, log_length, &log_length, log);
        
        return false;
    }

    return true;
}

void Program::attachShaders() {
    for (int i = 0; i < shaderList.size(); i++) {
        glAttachShader(id, shaderList.at(i)->getId());
    }
}

void Program::detachShaders() {
    for (int i = 0; i < shaderList.size(); i++) {
        glDetachShader(id, shaderList.at(i)->getId());
    }
}

void Program::compileShaders() {
    for (int i = 0; i < shaderList.size(); i++) {
        shaderList.at(i)->compile();
    }
}

void Program::createShader(const char* source, GLenum type) {
    shaderList.push_back(new Shader(source, type));
}

void Program::use() {
    glUseProgram(id);
}

unsigned int Program::getUniform(const char* name) {
    unsigned int uniform = glGetUniformLocation(id, name);

    return uniform;
}

unsigned int Program::getAttrib(const char* name) {
    unsigned int attrib = glGetAttribLocation(id, name);

    return attrib;
}

unsigned int Program::getId() {
    return id;
}

const char* Program::getGLSLversion() {
    std::string version;

	if(version.empty()) {

		version = "#version ";

		std::string glsl = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));

		for(char c : glsl)
		{
			if(isspace(c)) break;
			if(isdigit(c)) version += c;
		}
		version += '\n';
	}

    return version.c_str();
}