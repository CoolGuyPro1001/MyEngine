if(WIN32)
    if(ENABLE_INPUT)
        add_subdirectory(XInput)
    endif()

    add_subdirectory(DirectX)
endif()

if(UNIX)
    if(ENABLE_RENDERING)
        add_subdirectory(OpenGL)
    endif()

    add_subdirectory(SDL)
endif()
