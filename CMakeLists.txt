# Information about the project
cmake_minimum_required(VERSION 3.21)
project(a9 LANGUAGES C)

set(CMAKE_BUILD_TYPE "Debug")

# Include Pthreads package
find_package(Threads REQUIRED)

# Add compilier/linker options
add_compile_options(-Wall -Wextra -Wfatal-errors)
add_compile_options(-Werror=vla -Wno-unused -Wno-unused-parameter)
add_compile_options(-fsanitize=address -fsanitize=undefined)
add_link_options(-fsanitize=address -fsanitize=undefined)

# Add Part A
add_executable(parta_main src/parta.c src/parta.h)
target_link_libraries(parta_main Threads::Threads)

# Add Part B
add_executable(partb_main src/partb.c src/partb.h)
target_link_libraries(partb_main Threads::Threads)

# Add Part C
add_executable(partc_main src/partc.c src/partc.h)
target_link_libraries(partc_main Threads::Threads m)
target_include_directories(partc_main PUBLIC ${CMAKE_SOURCE_DIR}/extern/include)

# Add Part C (Sample)
add_executable(partc-sample src/partc-sample.c src/partc.h)
target_link_libraries(partc-sample Threads::Threads m)
target_include_directories(partc-sample PUBLIC ${CMAKE_SOURCE_DIR}/extern/include)

