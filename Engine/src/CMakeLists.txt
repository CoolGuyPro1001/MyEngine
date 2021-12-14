target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Actor.h
    Controller.h
    Events.h
    Level.h

    Actor.cpp
    Controller.cpp
    Events.cpp
    Level.cpp
)

add_subdirectory(Common)
add_subdirectory(Components)
add_subdirectory(Core)
#add_subdirectory(GUI)
