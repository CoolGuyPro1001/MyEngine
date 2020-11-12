target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Actor.h
    Controller.h
    Course.h
    Events.h
    File.h
    Level.h

    Actor.cpp
    Controller.cpp
    Events.cpp
    File.cpp
    Level.cpp
)

add_subdirectory(Common)
add_subdirectory(Core)
add_subdirectory(Graphics)