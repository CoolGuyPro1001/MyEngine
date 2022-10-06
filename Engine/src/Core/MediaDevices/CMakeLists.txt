if(ENABLE_INPUT)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        InputDevice.h

        InputDevice.cpp
    )
endif()
