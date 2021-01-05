find_package(SDL2 REQUIRED)

add_executable(playground playground.cpp)
target_include_directories(playground PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(playground LIBIMGUI ${SDL2_LIBRARIES})