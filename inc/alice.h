// ALICE.h
// Originally used because ALICE was the image being loaded.
// Now I probably should give it a name.
// Call it "A Loading Image Central Explorer"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ALICE {
    public:
        unsigned char* pixels;
        int width, height, channel;

        ALICE();

        unsigned char* loadImage(const char* file)
        void freePixels();

        GLuint LoadTexture(ALICE alice);
}