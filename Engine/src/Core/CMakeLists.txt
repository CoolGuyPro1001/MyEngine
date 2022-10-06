target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Entry.h
    Time.h
    Systems.h

    Entry.cpp
    Time.cpp
    Systems.cpp
)

add_subdirectory(Media)
add_subdirectory(MediaBackends)
add_subdirectory(MediaDevices)
