cmake_minimum_required(VERSION 3.16)
project(HW2_C_Cpp)

# Compiler flags
set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wwrite-strings -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wwrite-strings -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Decoration set flags
set(SOURCE_DIRECTORY project/src)
set(INCLUDE_DIRECTORY project/include)

add_subdirectory(project/tests)

# Find libraries for multi-thread work
find_package(Threads REQUIRED)

# Create static library matrix_one_thread
add_library(lib_matrix_one_thread STATIC ${SOURCE_DIRECTORY}/matrix_one_thread.c)
target_include_directories(lib_matrix_one_thread PUBLIC ${INCLUDE_DIRECTORY})

# Create static library matrix_multi_thread
add_library(lib_matrix_multi_thread SHARED ${SOURCE_DIRECTORY}/matrix_multi_thread.c)
target_include_directories(lib_matrix_multi_thread PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(lib_matrix_multi_thread Threads::Threads)
