cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(glad)

add_library(glad STATIC)

target_sources(glad PRIVATE src/glad.c)

target_include_directories(glad PUBLIC include/)
