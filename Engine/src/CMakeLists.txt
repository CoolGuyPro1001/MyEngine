target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Actor.h
    Component.h
    Level.h

    Actor.cpp
    Level.cpp
)

if(ENABLE_EVENTS)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        Events.h
    )

    add_subdirectory(Events)
endif()

if(ENABLE_GUI)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        GUI.h
    )

    add_subdirectory(GUI)
endif()

add_subdirectory(Common)
add_subdirectory(Components)
add_subdirectory(Core)
