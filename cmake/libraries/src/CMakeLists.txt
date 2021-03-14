add_executable(example main.cpp)
add_subdirectory(utility)
add_subdirectory(functional)
target_link_libraries(example PRIVATE functional)
