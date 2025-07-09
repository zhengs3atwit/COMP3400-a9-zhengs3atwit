# README

## Introduction

In this assignment, you'll be practicing using the POSIX pthreads API.

### Build Instructions

To build this project, first clone from GitHub. In the terminal, run the following command to
first prepare the build (this is done once, to prepare the directory called `build`):

    cmake -B build

To actually do the build, run the following command (`build` the project to the directory called
`build`) *every time you change a file*:

    cmake --build build

### Commit Instructions

After completing some code, first add the file called `src/parta.c` to staging:

    git add src/parta.c

Then do the actual commit:

    git commit -m 'Completed Part A'

Do the same after every function/file completed.

When you are ready to submit the assignment, run the following command:

    git push

## Part A

In this part, we'll be practicing using the pthreads API to create and work with threads. You are to
write a program that creates an arbitrary number of threads and print some output. Each child should
print:

    Hello, I'm thread X

with X being an ID number (0 through N-1). Note that this number is your own ID number, not
`tid`, which is what the C runtime and the Linux kernel uses to distinguish between different
threads.

At the end, once all threads are done (aka "joined"), have the main thread print

    Main cleans up

For example, if we pass 4 as an argument, we should get something like the following:

    $ ./build/parta_main 4
    Hello, I'm thread 0
    Hello, I'm thread 2
    Hello, I'm thread 3
    Hello, I'm thread 1
    Main cleans up

Remember, the scheduler can schedule the threads in any order! Just make sure the main thread prints last.

### The Task

First, get the number of threads from the command line argument. To get the number of threads, use
can use the function atoi() to convert a string (that was passed to argv) to an integer, like so:

    const char* input = "7";
    int nThreads = atoi(input);

Read the atoi manpage. What would happen if you provide a non-string as input (say "a") and tried to use atoi? Make sure
you handle this case correctly.

Then, create an int array and fill it with 0 through N-1. Note that because the length of the array
is not known *beforehand* (it's passed by command line), you need to use `malloc`.

Next, create an array of `pthread_t` variables and use a loop to call pthread_create. To pass
arguments to threads, you should create a variable in the heap, and pass a pointer to that variable
as the last argument to `pthread_create`.

Last, create *another* loop to call join on all the threads. Once the threads are done, print
"Hello, I'm main" and exit.

To run with 4 threads, use the following as stated above:

    $ ./build/parta_main 4
    Hello, I'm thread 0
    Hello, I'm thread 2
    Hello, I'm thread 3
    Hello, I'm thread 1
    Main cleans up

To run the unit tests, run:

    ./extern/bats/bin/bats tests/parta.bats

## Part B

In this part, let's initialize an array of integers using threads. You are to write a program that
creates an arbitrary number of threads. Each thread will be given a subset of the array, and
initialize them to its ID number. When the threads are done, the main thread will print the numbers.

For example, if we pass 2 as an argument, we should get something like the following:

    ./build/partb_main 2
    0,0,0,0,0,0,0,0
    0,0,0,0,0,0,0,0
    1,1,1,1,1,1,1,1
    1,1,1,1,1,1,1,1

but if we pass 4 as an argument, we should get something like:

    ./build/partb_main 4
    0,0,0,0,0,0,0,0
    1,1,1,1,1,1,1,1
    2,2,2,2,2,2,2,2
    3,3,3,3,3,3,3,3

For the threads to work the threads need some additional information. Instead of a simple integer
(like from Part A), the main thread now prepares a struct for each thread:

    struct thread_arg {
        int value;      /// The value to fill each element with
        int* array;     /// Pointer to the entire array
        int start_idx;  /// Starting index for this thread
        int end_idx;    /// End index for this thread
    };

The struct contains the value each element of the array should be filled with (thread 0 sets every
element to 0, thread 1 to 1, and so on). It also contains a pointer to the array, and the start and
end index that this thread is responsible for.

For example, from the first example (./build/partb_main 2), thread 0 will set every element of the
the first half of the array to 0. Thread 1 will set every other element to 1. The args should be:

    args[0].value = 0;
    args[0].array = array;
    args[0].start_idx = 0;
    args[0].end_idx = ARRAY_LEN / 2 - 1;
    pthread_create(&tid, NULL, &thread_main, &args[0]);

    args[1].value = 1;
    args[1].array = array;
    args[1].start_idx = ARRAY_LEN / 2;
    args[1].end_idx = ARRAY_LEN - 1;
    pthread_create(&tid, NULL, &thread_main, &args[1]);

To run with 4 threads, use the following as stated above:

    ./build/partb_main 4
    0,0,0,0,0,0,0,0
    1,1,1,1,1,1,1,1
    2,2,2,2,2,2,2,2
    3,3,3,3,3,3,3,3

and to run the unit tests, run:

    ./extern/bats/bin/bats tests/partb.bats

## Part C

In this assignment we will use the pthreads API to modify an existing single-threaded program to use
multiple threads. The file partc-sample.c contains a single-threaded program that uses the STB
library to load and manipulate images.  It uses the STB library to manipulate an image (provided as
a PNG file) and resample the colors of the image.

Using this program as a reference, write a program that does the same task, but using multple threads.

### Background: Image Processing

Each pixel is composed of color channels, and would commonly be red, green, and blue. This is called the 24-bit RGB
color scheme, since we have 3 colors with 1 byte (8 bits) each. In this scheme, a single pixel red dot would be
3 bytes: (255, 0, 0). A single green pixel would be (0, 255, 0), and a single blue pixel would be (0, 0, 255).

The pixels are then laid out as a 2D matrix, one for each pixel. So, a 2x2 pixel would be:

    [R0][G0][B0][R1][G1][B1][R2][G2][B2][R3][G3][B3]

For a total of 12 bytes (4 pixels, 3 bytes each).

### Background: STB Library

The file partc-sample.c contains a single-threaded version of an image processing program. The
program uses the following two files from the STB library:

- stb_image.h
- stb_image_write.h 

The first file is used to load images and contains the `stbi_load` function and the
`stbi_image_free` function that we will be using. The second file is used to save images and
contains the `stbi_write_png` function.

To load the PNG file, we need to use the `stbi_load` function. This function has the following
signature:

    uint8_t* stbi_load(const char* filename, int* p_width, int* p_height, int* p_channel, int unused);

The first argument is the filename to use, and is passed in through the first command-line argument.
The second and third arguments are output arguments to the width and height of the image. The 4th
argument is the channel, which is explained above. The last argument is unused and is always 0.

The STB library will load the PNG file contents and convert it so that the image data is load out
like the description above. This image data is returned as a malloc'd array of uint8_t, which is an
8-bit unsigned integer (i.e. a byte).

You can use the following code as an example:

    char* filename = "A.png";
    int width = 0;
    int height = 0;
    int channel = 0;
    uint8_t* data = stbi_load(filename, &width, &height, &channel, 0);

To save the PNG file, we use the `stbi_write_png` function. This function has the following
signature:

    int stbi_write_png(const char* filename, int width, int height, int channel, unsigned char* data, int row_length);

The first argument is the filename to use, and is passed in through the second command-line
argument. The second and third arguments are the width and height of the image, as explained above.
The 4th argument is the channel, also explained above. The 5th argument is the data to save, and the
last argument is the number of bytes per row.

The STB library will save the image data to a PNG file.

Lastly, the STB library creates the image data on the heap, so we need to clean up after ourselves,
as any model citizen will do. Use the `stbi_image_free` function to do so.

### Work To do

In this assignment we will use threads to parallelize the image processing among multiple threads.
The basic idea of the program will be identical to example program given, but now we accept an
additional command line argument: the number of threads to use.

Using the code as the starting point, modify it to create threads and distribute rows to each
thread. If the rows are not dividable by N, then give slightly less to the last thread. For example,
if you have an image with 48 rows, give each thread 12 rows. If you have an image with 45 rows,
however, you can give 3 threads 12 rows and the last one 9 rows. Note that in this case you need to
make sure the last thread does *not* process 12 rows and *not* step outside the buffer.

To summarize you program will:

1. Your program will load an image.
2. Your program will create N threads.
3. Distribute equal number of rows to each thread (except for the last one).
4. Manipulate each channel of each pixel in the image.
5. Wait for everyone to complete the work.
6. Save the image.

Your program should accept 3 arguments on the command line:

1. The input image filename.
2. The output image filename.
3. The number of threads to use.

### Test Cases

There will be 4 test cases provided.

- 1D Red Line: A simple 1D (width 200, height 1) red image (colors in RGB: 237 28 36).
- 2D Red Box: A simple 1D (width 64, height 48) red image (colors in RGB: 237 28 36). 
- Assorted: A more complicated image with assorted shapes.
- Pencils: A very large image with various colored pencils. This one has RGBA channels (4 total),
  where A represents transparency.


To process the file `red_box.png` with 4 threads, use the following as stated above:

    ./build/partc tests/red_box.png out.png 4

This assignment can take a very long time to complete (minutes). You can view your program results
by opening the [file](out.png) in vscode. You can also check the "correct" file by running
partc-sample:

    ./build/partc-sample tests/red_box.png out-sample.png

and seeing how it's different from your file

To run the unit tests, run:

    ./extern/bats/bin/bats tests/partc.bats