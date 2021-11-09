# Create exe-file for stress testing
add_executable(sync_stress_test.out sync_stress_test.c)
target_link_libraries(sync_stress_test.out lib_matrix_one_thread Threads::Threads)
target_include_directories(sync_stress_test.out PUBLIC ../../include)


# Create exe-file for time testing
add_executable(sync_time_test.out sync_time_test.c)
target_link_libraries(sync_time_test.out lib_matrix_one_thread Threads::Threads)
target_include_directories(sync_time_test.out PUBLIC ../../include)
