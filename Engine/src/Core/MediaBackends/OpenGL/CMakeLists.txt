find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(
    ${ENGINE_NAME}
    PUBLIC
    OpenGL::GL
    GLEW::GLEW
)

target_include_directories(
    ${ENGINE_NAME}
    PUBLIC
    ${GLM_INCLUDE_DIRS}
)

target_precompile_headers(
    ${ENGINE_NAME}
    PUBLIC
    OGLHeaders.h
)

target_sources(
    ${ENGINE_NAME}
    PRIVATE

    OGLBuffer.h
    OGLDebug.h
    OGLGraphics.h
    OGLMath.h
    OGLShader.h
    OGLTextureManager.h

    OGLDebug.cpp
    OGLGraphics.cpp
    OGLMath.cpp
    OGLShader.cpp
    OGLTextureManager.cpp
)

add_subdirectory(OGLBuffers)
