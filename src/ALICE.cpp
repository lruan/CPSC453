/*
ALICE.CPP
CPSC 453 - Homework 3
Written by Mingxi (Logan) Ruan

Code Contributions and Sources listed where appropriate.
*/

/*
    Class logic for ALICE.h.
    Moved out of main.cpp from HW2.
    Otherwise identiacl.
*/

#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>

#include "alice.h"
#include "stb_image.h"

ALICE::ALICE() {
    pixels = nullptr;
}

unsigned char* ALICE::loadImage(const char* file) {
    pixels = stbi_load(file, &width, &height, &channel, 0);

    return pixels;
}

void ALICE::freePixels() {
    stbi_image_free(pixels);
}
