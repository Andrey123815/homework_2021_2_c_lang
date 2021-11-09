add_subdirectory(sync)
add_subdirectory(async)

# Create exe-file for get_result of stress testing
add_executable(stress_test.out gtest_stress_tests.cpp)
target_link_libraries(stress_test.out ${GTEST_LIBRARIES} Threads::Threads)
target_include_directories(stress_test.out PUBLIC ../include)
