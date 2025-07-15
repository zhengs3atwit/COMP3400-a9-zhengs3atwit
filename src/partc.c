/*
Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) is licensed under a
Creative Commons Attribution-NonCommercial 3.0 Unported License
(http://creativecommons.org/licenses/by-nc/3.0/).
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
#include <pthread.h>
#include <stdio.h>

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
 * thread_arg struct. Contains the data, and the variables associated with it;
 * height, width, etc. Created and filled with specific values for specific
 * thread to work on (start_row & end_row)
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
 * thread_main function. Passed a struct pointer. containing the data, start row
 * end row, width, height and channels specific to the thread.
 * Loops through the data based on the values in the struct and modifies it
 *
 * @param args: pointer to a struct. containing calculated value of start_row,
 * end_rows in which the current thread will work on
 * @returns NULL
 */
void* thread_main(void* args) {
    // sets the arg pointer to struct thread_arg
    struct thread_arg* theStruct = (struct thread_arg*)args;

    // Loops through data from the structs start row to the end row modifying
    // the data.
    for (int row = theStruct->start_row; row < theStruct->end_row; row++) {
        for (int col = 0; col < theStruct->width; col++) {
            int r_index = (col + theStruct->width * row) * theStruct->channels;
            for (int c = 0; c < theStruct->channels; c++) {
                if (theStruct->data[r_index + c] > 127) {
                    theStruct->data[r_index + c] = 255;
                } else {
                    theStruct->data[r_index + c] = 0;
                }
            }
        }
    }

    return NULL;
}

/**
 * This program reads the number of threads to use and an image file. Each
 * thread is assigned 1/4 of the rows of pixels, and down-samples each color
 * pixel into an 8-bit color image.
 */
int main(int argc, char* argv[]) {
    // Checks if argument count is valid
    if (argc < 4) {
        printf("USAGE: partc_main IN_FILE OUT_FILE NTHREADS");
        return 1;
    }
    int numThreads = atoi(argv[3]);
    // Checks if number of threads is valid/positive
    if (numThreads < 1) {
        printf("ERROR: NTHREADS should be positive integer\n");
        return 1;
    }

    const char* infile = argv[1];
    const char* outfile = argv[2];

    // Load the data
    int width = 0;
    int height = 0;
    int channel = 0;
    uint8_t* data = stbi_load(infile, &width, &height, &channel, 0);

    if (data == NULL) {
        printf("Error loading image.\n");
        return 1;
    }
    // Calculate the rows and remainder
    int rows = (height / numThreads);
    int remainder = (height % numThreads);

    pthread_t* threadArray = malloc(sizeof(pthread_t) * numThreads);
    // Checks if malloc allocation if successful if not frees the loaded image
    // and return 1
    if (threadArray == NULL) {
        perror("malloc failed");
        stbi_image_free(data);
        return 1;
    }
    // Loops through for number of threads
    for (int i = 0; i < numThreads; i++) {
        // Creates struct
        struct thread_arg* theStruct = malloc(sizeof(struct thread_arg));
        // Check if malloc was successful
        if (theStruct == NULL) {
            perror("malloc failed for thread arguments");
            stbi_image_free(data);
            free(threadArray);
            return 1;
        }

        // Assign the data and image dimensions to the struct
        theStruct->data = data;
        theStruct->width = width;
        theStruct->height = height;
        theStruct->channels = channel;

        // Sets start and end rows for the struct
        theStruct->start_row = (i * rows);
        theStruct->end_row = (i + 1) * (rows);

        // Checks if i is end, if so add remainders
        if (i == (numThreads - 1)) {
            theStruct->end_row += remainder;
        }
        // Creates threads and check if it was successful
        if (pthread_create(&threadArray[i], NULL, thread_main, theStruct) !=
            0) {
            perror("ERROR: thread creation");
            free(theStruct);
            stbi_image_free(data);
            free(threadArray);
            return 1;
        }
    }
    // Loops through threads confirm finish
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threadArray[i], NULL);
    }

    // Save the data
    int ret =
        stbi_write_png(outfile, width, height, channel, data, width * channel);
    // Checks if save was successful
    if (ret == 0) {
        stbi_image_free(data);
        printf("Error writing file\n");
        return 1;
    }

    // Cleanup
    stbi_image_free(data);
    free(threadArray);

    return 0;
}
