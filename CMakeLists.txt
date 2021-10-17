cmake_minimum_required(VERSION 3.16)
project(HW2_C_Cpp)

set(CMAKE_C_STANDARD 99)
set(SOURCE_DIRECTORY project/src)
set(INCLUDE_DIRECTORY project/include)
#set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
#set(CMAKE_C_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

# Create static library matrix_one_thread
add_library(lib_matrix_one_th STATIC ${SOURCE_DIRECTORY}/matrix_one_thread.c)
target_include_directories(lib_matrix_one_th PUBLIC ${INCLUDE_DIRECTORY}/matrix_one_thread.h)
add_executable(main_one_thread.out main_one_thread.c)
target_link_libraries(main_one_thread.out lib_matrix_one_th)

# Create static library matrix_multi_thread
add_library(lib_matrix_multi_th STATIC ${SOURCE_DIRECTORY}/matrix_multi_thread.c)
target_include_directories(lib_matrix_multi_th PUBLIC ${INCLUDE_DIRECTORY}/matrix_multi_thread.h)
add_executable(main_multi_thread.out main_multi_thread.c)
target_link_libraries(main_multi_thread.out lib_matrix_multi_th)

enable_testing()

# Find libraries for test
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

# Create exe-file for testing one_thread mode
add_executable(test_one_thread.out gtest_one_thread.cpp)
target_link_libraries(test_one_thread.out lib_matrix_one_th ${GTEST_LIBRARIES} Threads::Threads)

#[[# Create exe-file for testing multi_thread mode
add_executable(test_multi_th.out gtest.cpp)
target_link_libraries(test.out equa ${GTEST_LIBRARIES} Threads::Threads)]]
