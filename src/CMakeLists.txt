find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(Engine)
add_subdirectory(Editor)