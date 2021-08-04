#include "TextureManager.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

#include <glad/glad.h>

#include <string>

#include <iostream>

unsigned int textureManager::loadTexture(const char* file_path) {
    unsigned int id = -1;

    int width, height, nrChannels;

    unsigned char* data = stbi_load(file_path, &width, &height, &nrChannels, 0);

    if (!data) {
        std::cout << file_path << std::endl;

        return -1;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return id;
}

void textureManager::activateTexture(unsigned int id, unsigned int level) {
    glActiveTexture(GL_TEXTURE0 + level);
    glBindTexture(GL_TEXTURE_2D, id);
}

void textureManager::deactivateTexture(unsigned int level) {
    glActiveTexture(GL_TEXTURE0 + level);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}