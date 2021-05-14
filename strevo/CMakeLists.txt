set(GAME Strevo)
find_package(Engine64 REQUIRED)

add_executable(
    ${GAME}
    Strevo.cpp
    Strevo.h
    Main.cpp
)

target_link_libraries(
    ${GAME}
    PUBLIC
    ${ENGINE_NAME}
)