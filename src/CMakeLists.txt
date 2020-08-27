find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGL)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

add_definitions(${QT_DEFINITIONS})

set(PROJECT_SOURCES 
    Main.cpp
    Common/Binary.cpp
    Common/Hex.cpp
    Graphics/Graphics.cpp
    Graphics/IndexBuffer.cpp
    Graphics/VertexBuffer.cpp
    Graphics/Shader.cpp
    Graphics/GLDebug.cpp
    Graphics/Camera.cpp
    File.cpp
    Model.cpp
    Parse.cpp
    Directory.cpp
    QT/mainwindow.cpp
    QT/openglwidget.cpp
)

set(PROJECT_HEADERS
    Common/Binary.h
    Common/Hex.h
    Graphics/Graphics.h
    Graphics/IndexBuffer.h
    Graphics/VertexBuffer.h
    Graphics/Shader.h
    Graphics/Units.h
    Graphics/GLDebug.h
    Graphics/Camera.cpp
    File.h
    Directory.h
    Model.h
    Actor.h
    Course.h
    Parse.h
    QT/mainwindow.h
    QT/openglwidget.h
)

set(PROJECT_UI
    QT/mainwindow.ui
    QT/openglwidget.ui)

qt5_wrap_ui(UI_WRAP ${PROJECT_UI})
qt5_wrap_cpp(MOC_SOURCES ${PROJECT_HEADERS})



add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${UI_WRAP}
    ${MOC_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt::Core
    Qt::Widgets
    Qt::Gui
    Qt::OpenGL
    OpenGL::GL
    GLEW::GLEW
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::OpenGL> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)