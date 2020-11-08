cmake_minimum_required(VERSION 3.13)
project(TestingCoverage  VERSION 1.0.0.0 LANGUAGES  C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O0  -fprofile-arcs -ftest-coverage")

add_subdirectory(src)

add_executable(Tests tests.c)
target_link_libraries(Tests LibBuf)

include(CTest)

add_test(test_buffer_init Tests 0)
add_test(test_buffer_push_and_free Tests 1)
add_test(test_buffer_push Tests 2)
add_test(test_buffer_clear_empty Tests 3)
add_test(test_buffer_clear_not_empty Tests 4)
add_test(test_buffer_pop Tests 5)
add_test(test_buffer_grow_and_trunc Tests 6)
#add_test(test_buffer_grow_mem_failure Tests 7)
#add_test(test_buffer_trunc_mem_failure Tests 8)
#add_test(test_buffer_two_trunc_mem_failure Tests 9)
add_test(buffer_benchmark Tests 10)

add_custom_target(testing COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS Tests)
add_custom_target(testing_coverage COMMAND make ExperimentalCoverage DEPENDS testing)
add_custom_target(cleaning COMMAND rm -rf *)
add_custom_command(TARGET testing 
		COMMAND echo "target testing finished. to clean run make cleaning"
)

add_custom_command(TARGET testing_coverage
		COMMAND echo "target testing_coverage finished. to clean run make cleaning"
		COMMAND echo "Results will be in ./CoverageInfo"
		COMMAND cp -rf ./Testing/CoverageInfo ..
)

add_custom_command(TARGET cleaning
		COMMAND rm -rf ../CoverageInfo
)
