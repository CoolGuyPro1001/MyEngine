set(CMAKE_STATIC_LIBRARY_PREFIX "")

#OS Stuff
if(WIN32)
    set(OS "Win32")
endif()

if(UNIX)
    set(OS "Unix")
endif()

add_library(${ENGINE_NAME} STATIC)

#Output
set(BUILD_DIR "/Engine64")
set_target_properties(${ENGINE_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_DIR}/debug/lib/${OS}")
set_target_properties(${ENGINE_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BUILD_DIR}/release/lib/${OS}")


#Installation
install(
    TARGETS ${ENGINE_NAME}
    CONFIGURATIONS Debug
    LIBRARY DESTINATION Debug/lib
)
install(
    DIRECTORY src/
    DESTINATION Debug/include
    CONFIGURATIONS Debug
    FILES_MATCHING PATTERN "*.h"
)

install(
    TARGETS ${ENGINE_NAME}
    CONFIGURATIONS Release
    LIBRARY DESTINATION Release/lib
)
install(
    DIRECTORY src/
    DESTINATION Release/include
    CONFIGURATIONS Release
    FILES_MATCHING PATTERN "*.h"
)
install(CODE "MESSAGE(\"Are you ready to Mario time?\")")


#Build
file(
    COPY src/ 
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include 
    FILES_MATCHING PATTERN "*.h"
)

#Exportation
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

target_include_directories(${ENGINE_NAME}
    PUBLIC
    ${GLM_INCLUDE_DIRS}
    ${SDL2-INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Engine/src/
)

target_precompile_headers(
    ${ENGINE_NAME}
    PUBLIC
    pch.h
)

add_subdirectory(src)