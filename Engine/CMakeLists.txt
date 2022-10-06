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

get_target_property(F ${ENGINE_NAME} COMPILE_OPTIONS)
message("${F}")

message("Test")

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

target_include_directories(
    ${ENGINE_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/Engine/src/
)

target_precompile_headers(
    ${ENGINE_NAME}
    PUBLIC
    pch.h
)


#Module Flags
set(ENABLE_GUI          OFF CACHE BOOL "Enable GUI Support")
set(ENABLE_RENDERING    OFF CACHE BOOL "Enable 3D Rendering Support")
set(ENABLE_EVENTS       OFF CACHE BOOL "Enable Event Support")
set(ENABLE_INPUT        OFF CACHE BOOL "Enable Device Input Support")
set(ENABLE_TEXTURES     OFF CACHE BOOL "Enable Texture Support")
set(ENABLE_COLLISION    OFF CACHE BOOL "Enable Collision Support")
set(ENABLE_FONT         OFF CACHE BOOL "Enable Font Support")

if(ENABLE_INPUT)
    set(ENABLE_EVENTS ON)
endif()

if(ENABLE_TEXTURES OR ENABLE_GUI OR ENABLE_COLLISION)
    set(ENABLE_RENDERING ON)
endif()

add_subdirectory(src)
