if(ENABLE_RENDERING)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        GraphicsMedia.h
        WindowMedia.h

        WindowMedia.cpp
    )

    add_subdirectory(Graphics)
endif()

if(ENABLE_GUI)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        Graphics2DMedia.h
        WindowMedia.h

        WindowMedia.h
    )
endif()

if(ENABLE_INPUT)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        InputMedia.h
        InputCodes.h

        InputMedia.cpp
    )
endif()

if(ENABLE_FONT)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        FontMedia.h
    )
endif()
