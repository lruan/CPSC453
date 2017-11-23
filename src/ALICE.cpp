#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "alice.h"

ALICE::ALICE() {
    pixels = nullptr;
}

unsigned char* ALICE::loadImage(const char* file) {
    stbi_set_flip_vertically_on_load(true);
    pixels = stbi_load(file, &width, &height, &channel, 0);

    return pixels;
}

void ALICE:freePixels() {
    stbi_image_free(pixels);
}

GLuint ALICE::LoadTexture(ALICE alice) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if(alice.channel == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, alice.width, alice.height, 0, GL_RGB, GL_UNSIGNED_BYTE, alice.pixels);
    else if(alice.channel == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, alice.width, alice.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, alice.pixels);

    return texture;
}
}