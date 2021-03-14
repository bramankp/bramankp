add_library(functional Functional.cpp Functional.hpp)
target_include_directories(functional PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(functional PRIVATE utility)
