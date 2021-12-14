cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

#set(CMAKE_VERBOSE_MAKEFILE ON)

project(Edit64 VERSION 1.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(EDITOR_NAME Edit64)
set(ENGINE_NAME Engine64)

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(strevo)
