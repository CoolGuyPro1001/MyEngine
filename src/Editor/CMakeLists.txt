set(EDITOR_NAME Edit64)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGL)
find_package(Engine64 REQUIRED)

add_definitions(${QT_DEFINITIONS})

qt5_wrap_ui(UI_WRAP ${EDITOR_UI})
qt5_wrap_cpp(MOC_SOURCES ${EDITOR_HEADERS})

add_executable(
    ${EDITOR_NAME}
    ${UI_WRAP}
    ${MOC_SOURCES}
)

target_sources(
    ${EDITOR_NAME}
    PRIVATE

    Directory.h
    Parse.h
    
    Directory.cpp
    Parse.cpp
    Main.cpp
)

target_link_libraries(
    ${EDITOR_NAME}
    PUBLIC

    Qt::Core
    Qt::Widgets
    Qt::Gui
    Qt::OpenGL
    Engine64::Engine64
)

target_include_directories(
    ${EDITOR_NAME}
    PUBLIC

    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    ${Engine64_INCLUDE_DIRS}
)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::OpenGL> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)

add_subdirectory(QT)