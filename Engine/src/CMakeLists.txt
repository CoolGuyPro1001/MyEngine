target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Actor.h
    Collision.h
    Component.h
    Controller.h
    Events.h
    File.h
    Level.h
    Model.h
    Object.h
    Shapes.h

    Actor.cpp
    Collision.cpp
    Component.cpp
    Controller.cpp
    Events.cpp
    File.cpp
    Level.cpp
    Model.cpp
    Object.cpp
    Shapes.cpp
)

add_subdirectory(Common)
add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(GUI)