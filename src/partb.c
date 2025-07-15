#include "partb.h"
#include <pthread.h>
#include <stdio.h>

/**
 * This struct contains values that the main thread passes to each
 * child thread.
 */
struct thread_arg {
    int value;      /// The value to fill each element with
    int* array;     /// Pointer to the entire array
    int start_idx;  /// Starting index for this thread
    int end_idx;    /// End index for this thread
};

/** The length of the array to fill */
enum { ARRAY_LEN = 256 };
/** How many to print per line */
enum { PERLINE = 32 };

/**
 * print_array function takes in array and array len. Prints value of the array
 * and after it reaches 'PERLINE' amount of values it starts new line.
 *
 * @param array Array to print values from
 * @param alen Array length
 *
 * @return void
 */
void print_array(int* array, int alen) {
    // Loops through array and prints value, if reached end new line
    for (int i = 0; i < alen; i++) {
        printf("%d", array[i]);
        if ((i + 1) % PERLINE == 0) {
            printf("\n");
        } else {
            printf(",");
        }
    }
    printf("\n");
}

/**
 * This program uses threads to initialize an array of integers
 *
 * @argc Argument counter
 * @argv Arguments Array
 *
 * @return status of program
 */
int main(int argc, char* argv[]) {
    // Checks if argument counter is valid
    if (argc <= 1) {
        printf("USAGE: partb_main NTHREADS");
        return 1;
    }
    // Gets number of threads
    int numThreads = atoi(argv[1]);
    // Checks if number of threads is valid/positive
    if (numThreads < 1) {
        printf("ERROR: NTHREADS should be positive integer");
        return 1;
    }
    // malloc to allocate two arrays one for thread and other for the threads to
    // fill in
    int* fillArray = malloc(sizeof(int) * ARRAY_LEN);
    pthread_t* threadArray = malloc(sizeof(pthread_t) * numThreads);
    // Checks if malloc allocation worked
    if (fillArray == NULL || threadArray == NULL) {
        free(fillArray);
        free(threadArray);
        perror("malloc failed");
        return 1;
    }

    for (int i = 0; i < numThreads; i++) {
        struct thread_arg* theStruct = malloc(sizeof(struct thread_arg));

        // Checks if malloc was successful
        if (theStruct == NULL) {
            return 1;
        }
        // Sets value to the struct to be passed to each thread
        theStruct->value = i;
        theStruct->array = fillArray;
        theStruct->start_idx = i * (ARRAY_LEN / numThreads);
        theStruct->end_idx = (i + 1) * (ARRAY_LEN / numThreads) - 1;
        // Checks if i is last index, if so set end index to be array_len - 1
        if (i == (numThreads - 1)) {
            theStruct->end_idx = ARRAY_LEN - 1;
        }
        // Creates thread and gives function thrd_main, and theStruct; holding
        // values each thread needs to each individuals work like start index
        // and end index
        if (pthread_create(&threadArray[i], NULL, thrd_main, theStruct) != 0) {
            perror("ERROR: thread creation");
            return 1;
        }
    }
    // Loops through threads confirm finish
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threadArray[i], NULL);
    }

    // After threads are done filling array, calling print_array to print
    // Passing the array and length
    print_array(fillArray, ARRAY_LEN);
    // Free the malloc arrays
    free(fillArray);
    free(threadArray);

    return 0;
}

/**
 * thrd_main function. Gets passed a pointer to thread_arg struct.
 * Loops through array given in the struct assigning values given in the struct,
 * and starting at start_idx and end with end_idx values in the struct
 *
 * @param args Pointer to struct
 */
void* thrd_main(void* args) {
    struct thread_arg* theStruct = (struct thread_arg*)args;
    // Loops through from start index to end index of the struct
    // Sets the value in the given struct array to be the value set in the
    // struct
    for (int i = theStruct->start_idx; i <= theStruct->end_idx; i++) {
        theStruct->array[i] = theStruct->value;
    }
    free(theStruct);
    return NULL;
}