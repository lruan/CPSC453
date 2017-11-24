// ALICE.h
// Originally used because ALICE was the image being loaded.
// Now I probably should give it a name.
// Call it "A Loading Image Class Extension"

#pragma once

#include <GLFW/glfw3.h>

class ALICE {
    public:
        unsigned char* pixels;
        int width, height, channel;

        ALICE();

        unsigned char* loadImage(const char* file);
        void freePixels();

    };