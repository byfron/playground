find_package(Catch2 REQUIRED)
add_test(NAME test_vec3 COMMAND test_vec3)
enable_testing()

add_library(Tests tests-main.cpp)
target_link_libraries(Tests Catch2::Catch2)

add_executable(test_vec3 test_vec3.cpp)
target_link_libraries(test_vec3 Tests)
