# Find libraries for test
find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(productivity)

# Create exe-file for testing one-thread mode
add_executable(test_matrix_one_thread.out gtest_matrix_one_thread.cpp)
target_link_libraries(test_matrix_one_thread.out lib_matrix_one_thread ${GTEST_LIBRARIES} Threads::Threads)
target_include_directories(test_matrix_one_thread.out PUBLIC ../include)

# Create exe-file for testing multi-thread mode
add_executable(test_matrix_multi_thread.out gtest_matrix_multi_thread.cpp)
target_link_libraries(test_matrix_multi_thread.out lib_matrix_multi_thread ${GTEST_LIBRARIES} Threads::Threads)
target_include_directories(test_matrix_multi_thread.out PUBLIC ../include)
