cmake_minimum_required(VERSION 3.16)
project(test LANGUAGES C)

set(VERSION_BUILD 4)
set(SOURCES
    one.c
    two.c
    $<$<EQUAL:${VERSION_BUILD},5>:three.c>
)

add_executable(something ${SOURCES})
