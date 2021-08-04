#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

namespace textureManager {
    unsigned int loadTexture(const char* file_path);

    void activateTexture(unsigned int id, unsigned int level = 0);

    void deactivateTexture(unsigned int level = 0);
}

#endif