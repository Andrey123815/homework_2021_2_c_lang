# Create exe-file for stress testing
add_executable(async_stress_test.out async_stress_test.c)
target_link_libraries(async_stress_test.out lib_matrix_multi_thread Threads::Threads)
target_include_directories(async_stress_test.out PUBLIC ../../include)


# Create exe-file for time testing
add_executable(async_time_test.out async_time_test.c)
target_link_libraries(async_time_test.out lib_matrix_multi_thread Threads::Threads)
target_include_directories(async_time_test.out PUBLIC ../../include)
