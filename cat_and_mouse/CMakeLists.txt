set(GAME CatAndMouse)
find_package(Engine64 REQUIRED)

add_executable(
    ${GAME}
    Cat.cpp
    Cat.h
    Main.cpp
    Mouse.cpp
    Mouse.h
)

target_link_libraries(
    ${GAME}
    PUBLIC
    ${ENGINE_NAME}
)