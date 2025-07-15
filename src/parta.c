#include "parta.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  //for malloc

/**
 * This program creates threads and has each thread prints its own number and
 * exits
 *
 * @param argc Count of how many arguments
 * @param argv Arguments array
 *
 * @return status of program
 */
int main(int argc, char* argv[]) {
    // Checks if argument count is valid
    if (argc <= 1) {
        printf("USAGE: parta_main NTHREADS");
        return 1;
    }
    // Sets the thread amount to int
    int numThreads = atoi(argv[1]);
    // Checks if thread amount is valid/positive
    if (numThreads < 1) {
        printf("ERROR: NTHREADS should be positive integer\n");
        return 1;
    }
    // Uses malloc to allocate two array one holding ID value for threads to
    // print and other for system
    int* threadIds = malloc(sizeof(int) * numThreads);
     if (threadIds == NULL) {
        perror("malloc failed");
        return 1;
    }
    pthread_t* threadsArray = malloc(sizeof(pthread_t) * numThreads);
    // Checks if malloc allocation was successful
    if (threadsArray == NULL) {
        perror("malloc failed");
        free(threadIds);
        return 1;
    }
    // Loops through amount of threads
    for (int i = 0; i < numThreads; i++) {
        // Sets value at index i to be equal to i
        threadIds[i] = i;
        // Creates thread, has it run thrd_main function with the argument of
        // value at threadIds[i]. If fail free the malloc arrays and return 1
        if (pthread_create(&threadsArray[i], NULL, thrd_main, &threadIds[i]) !=
            0) {
            perror("ERROR: thread creation");
            free(threadIds);
            free(threadsArray);
            return 1;
        }
    }
    // Loops through threads confirm finish
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threadsArray[i], NULL);
    }

    // Code done. Frees arrays
    free(threadIds);
    free(threadsArray);

    printf("Main cleans up\n");

    return 0;
}

/**
 * thrd_main function. Is called/used by crated threads to print their ID values
 *
 * @param args Passed ID value of the thread
 *
 * @return void
 */
void* thrd_main(void* args) {
    // Cast int to args, and then dereferences it to access the value
    int threadId_Values = *(int*)args;
    printf("Hello, I'm thread %d\n", threadId_Values);
    return NULL;
}
