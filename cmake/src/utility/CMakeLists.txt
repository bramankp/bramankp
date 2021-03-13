add_library(utility Utility.cpp Utility.hpp)
target_include_directories(utility PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
