#include "partb.h"
#include <stdio.h>
#include <pthread.h>

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
 * TODO: Complete and document
 */
void print_array(int* array, int alen) {
}

/**
 * This program uses threads to initialize an array of integers
 */
int main(int argc, char* argv[]) {
    // TODO: Complete and document

    return 0;
}

/**
 * TODO: Complete and document
 */
void* thrd_main(void* args) {
    // TODO: Complete and document
    return NULL;
}

