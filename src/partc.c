/*
Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) is licensed under a Creative Commons
Attribution-NonCommercial 3.0 Unported License (http://creativecommons.org/licenses/by-nc/3.0/).
*/
//
// This program uses the STB library (http://nothings.org/)
// which points to the code at: https://github.com/nothings/stb
//
// This library enables you to load images (png, jpg, etc).
// You can then manipulate the images at the pixel level.
// Then you can save the pixels as an image.
//
#include "partc.h"
#include <stdio.h>
#include <pthread.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wdeprecated"

#define STBI_NO_SIMD
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma GCC diagnostic pop

/**
 * TODO: Describe this struct
 */
struct thread_arg {
    unsigned char* data;
    int width;
    int height;
    int channels;
    int start_row;
    int end_row;
};


/**
 * TODO: Describe this function. In particular, focus on how work is distributed
 * among threads.
 *
 * @param args: TODO: Describe the contents of arg
 * @returns NULL
 */
void *thread_main(void *args) {
    // TODO: Complete and document

    return NULL;
}

/**
 * This program reads the number of threads to use and an image file. Each thread is assigned 1/4 of
 * the rows of pixels, and down-samples each color pixel into an 8-bit color image.
 */
int main(int argc, char *argv[]) {
    // TODO: Complete and document  
	return 0;
}
