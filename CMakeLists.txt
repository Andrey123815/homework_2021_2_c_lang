cmake_minimum_required(VERSION 3.16)
project(HW2_C_Cpp)

set(CMAKE_C_STANDARD 99)
set(SOURCE_DIRECTORY project/src)
set(INCLUDE_DIRECTORY project/include)
#set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
#set(CMAKE_C_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Create static library matrix_one_thread
add_library(lib_matrix_one_thread STATIC ${SOURCE_DIRECTORY}/matrix_one_thread.c)
target_include_directories(lib_matrix_one_thread PUBLIC ${INCLUDE_DIRECTORY}/matrix_one_thread.h)
add_executable(main_matrix_one_thread.out project/main_matrix_one_thread.c)
target_link_libraries(main_matrix_one_thread.out lib_matrix_one_thread)

# Create static library matrix_multi_thread
add_library(lib_matrix_multi_thread STATIC ${SOURCE_DIRECTORY}/matrix_multi_thread.c)
target_include_directories(lib_matrix_multi_thread PUBLIC ${INCLUDE_DIRECTORY}/matrix_multi_thread.h)
add_executable(main_matrix_multi_thread.out project/main_matrix_multi_thread.c)
target_link_libraries(main_matrix_multi_thread.out lib_matrix_multi_thread)

enable_testing()

# Find libraries for test
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Create exe-file for testing one-thread mode
add_executable(test_matrix_one_thread.out project/tests/gtest_matrix_one_thread.cpp)
target_link_libraries(test_matrix_one_thread.out lib_matrix_one_thread ${GTEST_LIBRARIES} Threads::Threads)

# Create exe-file for testing multi-thread mode
#[[add_executable(test_matrix_multi_thread.out gtest_matrix_multi_thread.cpp)
target_link_libraries(test_matrix_multi_thread.out lib_matrix_multi_thread ${GTEST_LIBRARIES} Threads::Threads)]]
