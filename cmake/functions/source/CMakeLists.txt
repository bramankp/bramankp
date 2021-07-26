function(set_standard_build_options tgt)
    set_property(TARGET ${tgt} PROPERTY C_STANDARD 11)
    target_compile_options(${tgt} PRIVATE -Wall -Wextra -O3)
endfunction()

function(add_standard_library tgt)
    add_library(${tgt} ${ARGN})
    target_include_directories(something PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
    set_standard_build_options(${tgt})
endfunction()

add_executable(functions main.c)
set_standard_build_options(functions)
target_link_libraries(functions PRIVATE something)

add_subdirectory(libsomething)
