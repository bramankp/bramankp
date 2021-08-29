cmake_minimum_required(VERSION 3.16)

project(threads LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(threads main.cpp)
set_property(TARGET threads PROPERTY CXX_STANDARD 17)
target_compile_options(threads PRIVATE -Wall -Wextra -Werror -O3)
target_link_libraries(threads PRIVATE Threads::Threads)
