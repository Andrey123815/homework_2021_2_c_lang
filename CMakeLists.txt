cmake_minimum_required(VERSION 3.16)
project(HW2_C_Cpp)


# Compiler flags
set(CMAKE_C_STANDARD 99)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


# Decoration set flags
set(TESTS project/tests)
set(SOURCE_DIRECTORY project/src)
set(INCLUDE_DIRECTORY project/include)
set(SERVICE_SRC project/tests/service_module/src)


# Create static library matrix_one_thread
add_library(lib_matrix_one_thread STATIC ${SOURCE_DIRECTORY}/matrix_one_thread.c)
target_include_directories(lib_matrix_one_thread PUBLIC ${INCLUDE_DIRECTORY})
add_executable(main_matrix_one_thread.out project/main_matrix_one_thread.c)
target_link_libraries(main_matrix_one_thread.out lib_matrix_one_thread)


# Find libraries for multi-thread work
find_package(Threads REQUIRED)


# Create static library matrix_multi_thread
add_library(lib_matrix_multi_thread SHARED ${SOURCE_DIRECTORY}/matrix_multi_thread.c)
target_include_directories(lib_matrix_multi_thread PUBLIC ${INCLUDE_DIRECTORY})
target_link_libraries(lib_matrix_multi_thread Threads::Threads)
add_executable(main_matrix_multi_thread.out project/main_matrix_multi_thread.c)
target_link_libraries(main_matrix_multi_thread.out lib_matrix_multi_thread)


enable_testing()


# Find libraries for test
find_package(GTest REQUIRED)


# Create exe-file for testing one-thread mode
add_executable(test_matrix_one_thread.out ${TESTS}/gtest_matrix_one_thread.cpp)
target_link_libraries(test_matrix_one_thread.out lib_matrix_one_thread ${GTEST_LIBRARIES} Threads::Threads)


# Create exe-file for testing multi-thread mode
add_executable(test_matrix_multi_thread.out ${TESTS}/gtest_matrix_multi_thread.cpp)
target_link_libraries(test_matrix_multi_thread.out lib_matrix_multi_thread ${GTEST_LIBRARIES} Threads::Threads)


# Create exe-files for stress testing
add_executable(stress_test_one_thread.out ${SERVICE_SRC}/write_stress_tests.c
        ${SERVICE_SRC}/lib_generator.c ${SERVICE_SRC}/lib_stress_test.c)
target_link_libraries(stress_test_one_thread.out lib_matrix_one_thread Threads::Threads)
add_executable(stress_test_multi_thread.out ${SERVICE_SRC}/write_stress_tests.c
        ${SERVICE_SRC}/lib_generator.c ${SERVICE_SRC}/lib_stress_test.c)
target_link_libraries(stress_test_multi_thread.out lib_matrix_multi_thread Threads::Threads)
add_executable(stress_test.out ${TESTS}/gtest_stress_tests.cpp ${SERVICE_SRC}/lib_stress_test.c)
target_link_libraries(stress_test.out ${GTEST_LIBRARIES} Threads::Threads)


# Create exe-files for time testing
add_executable(time_test_one_thread.out ${TESTS}/time_test.c
        ${SERVICE_SRC}/lib_time_test.c ${SERVICE_SRC}/lib_generator.c)
target_link_libraries(time_test_one_thread.out lib_matrix_one_thread Threads::Threads)
add_executable(time_test_multi_thread.out ${TESTS}/time_test.c
        ${SERVICE_SRC}/lib_time_test.c ${SERVICE_SRC}/lib_generator.c)
target_link_libraries(time_test_multi_thread.out lib_matrix_multi_thread Threads::Threads)
