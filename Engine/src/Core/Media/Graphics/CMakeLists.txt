target_sources(
    ${ENGINE_NAME}
    PRIVATE

    GraphicsBuffer.h
    Texture.h

    GraphicsBuffer.cpp
)

add_subdirectory(Texture)
