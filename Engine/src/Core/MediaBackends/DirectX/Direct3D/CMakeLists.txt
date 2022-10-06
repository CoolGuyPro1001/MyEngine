target_link_libraries(
    ${ENGINE_NAME}
    PUBLIC
    d3d12.lib
)

target_precompile_headers(
    ${ENGINE_NAME}
    PUBLIC
    D3DHeaders.h
)

target_sources(
    ${ENGINE_NAME}
    PRIVATE

    D3DGraphics.h
    D3DMath.h
    D3DShader.h

    D3DGraphics.cpp
    D3DMath.cpp
    D3DShader.cpp
)
add_subdirectory(D3DBufferManagers)
