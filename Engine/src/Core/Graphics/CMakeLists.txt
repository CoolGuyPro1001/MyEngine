target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Buffer.h
    GLDebug.h
    Graphics.h
    Shader.h
    Texture.h

    GLDebug.cpp
    Graphics.cpp
    Shader.cpp
)

add_subdirectory(Texture)
add_subdirectory(Buffers)
