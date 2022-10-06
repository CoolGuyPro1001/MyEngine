find_package(SDL2 REQUIRED)

target_link_libraries(
    ${ENGINE_NAME}
    PUBLIC
    SDL2::SDL2
)

target_include_directories(
    ${ENGINE_NAME}
    PUBLIC
    ${SDL2_INCLUDE_DIRS}
)

target_precompile_headers(
    ${ENGINE_NAME}
    PUBLIC
    SDLHeaders.h
)

target_sources(
    ${ENGINE_NAME}
    PRIVATE

    SDLEvents.h
    SDLEvents.cpp
)

if(ENABLE_RENDERING)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        SDLWindow.h
        SDLWindow.cpp
    )
endif()

if(ENABLE_INPUT)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        SDLInput.h
        SDLInput.cpp
    )
endif()
