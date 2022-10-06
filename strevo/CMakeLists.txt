set(GAME Strevo)
find_package(Engine64 REQUIRED)

add_executable(
    ${GAME}
    Main.cpp
    Strevo.cpp
    Strevo.h
    #Sword.h
    #Sword.cpp
)

target_link_libraries(
    ${GAME}
    PUBLIC
    ${ENGINE_NAME}
)
