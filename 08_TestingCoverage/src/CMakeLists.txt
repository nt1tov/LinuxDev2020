cmake_minimum_required(VERSION 3.13)

#project(buflib)
set(SOURCES libbuf.c)
add_library(LibBuf STATIC  ${SOURCES})
# target_include_directories(lib ${CMAKE_CURRENT_SOURCE_DIR})

