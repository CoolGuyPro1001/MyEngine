find_package(PkgConfig REQUIRED)
pkg_check_modules(FREETYPE_PKG REQUIRED IMPORTED_TARGET freetype2)

target_link_libraries(
    ${ENGINE_NAME}
    PUBLIC
    PkgConfig::FREETYPE_PKG
)

target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Button.h
    Text.h
    Widget.h

    Button.cpp
    GUI.cpp
    Text.cpp
    Widget.cpp
)
