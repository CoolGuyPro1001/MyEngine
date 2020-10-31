set(ENGINE_NAME Engine64)
set(INCLUDE_PATH input)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_library(
    ${ENGINE_NAME}
)

export(
    TARGETS
    ${ENGINE_NAME}
    NAMESPACE ${ENGINE_NAME}::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/Engine64Config.cmake"
)

target_link_libraries(
    ${ENGINE_NAME}
    PUBLIC
    OpenGL::GL
    GLEW::GLEW
    SDL2::SDL2
)

target_include_directories(
    ${ENGINE_NAME}
    PRIVATE
    ${INCLUDE_PATH}
)

target_include_directories(${ENGINE_NAME}
    PUBLIC
    ${GLM_INCLUDE_DIRS}
    ${SDL2-INCLUDE_DIRS}
)

target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Actor.h
    Controller.h
    Course.h
    Events.h
    File.h
    Level.h

    Actor.cpp
    Controller.cpp
    Events.cpp
    File.cpp
    Level.cpp
)

target_precompile_headers(
    ${ENGINE_NAME}
    PUBLIC
    pch.h
)

add_subdirectory(Common)
add_subdirectory(Core)
add_subdirectory(Graphics)