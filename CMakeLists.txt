cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)

project(
  openglTest
  DESCRIPTION "Opengl practice"
  LANGUAGES C CXX)

set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

find_package(glfw3 CONFIG REQUIRED)

add_executable(output)

target_sources(
  output
  PRIVATE src/main.cpp
          src/ShaderClass.cpp
          src/VBO.cpp
          src/VAO.cpp
          src/EBO.cpp
          src/stb_image.c
          src/Textures.cpp
          src/Camera.cpp)

add_subdirectory(include/glad)

target_include_directories(output PRIVATE include)

target_link_libraries(output PRIVATE glad glfw)

add_custom_command(
  TARGET POST_BUILD
  output
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${RES_DIR}
          $<TARGET_FILE_DIR:output>/resources
  COMMENT "Copying shaders and textures to binary directory")
