add_library(prebuilt SHARED IMPORTED)
target_include_directories(prebuilt INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# manually tell CMake where to find the library
set_target_properties(prebuilt PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libprebuilt.so)

# manually tell CMake that this belongs to part of the greater build of code
set_target_properties(prebuilt PROPERTIES IMPORTED_GLOBAL TRUE)
