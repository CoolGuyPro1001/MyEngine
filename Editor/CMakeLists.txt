#find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGL)
#find_package(Engine64 REQUIRED)

#add_definitions(${QT_DEFINITIONS})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#qt5_wrap_ui(UI_WRAP ${EDITOR_UI})
#qt5_wrap_cpp(MOC_SOURCES ${EDITOR_HEADERS})

#add_executable(
#    ${EDITOR_NAME}
#)

#set_property(TARGET ${EDITOR_NAME} PROPERTY AUTOMOC ON)
#set_property(TARGET ${EDITOR_NAME} PROPERTY AUTOUIC ON)

#Output
#set(BUILD_DIR "/Edit64")
#set_target_properties(${EDITOR_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_DIR}/${OS}/bin")
#set_target_properties(${EDITOR_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_DIR}/${OS}/bin")


#Installation
#install(
#    TARGETS ${EDITOR_NAME}
#    CONFIGURATIONS Debug
#    LIBRARY DESTINATION Debug/bin
#)

#install(
#    TARGETS ${EDITOR_NAME}
#    CONFIGURATIONS Release
#    LIBRARY DESTINATION Release/bin
#)
install(CODE "MESSAGE(\"Are you ready to Luigi time?\")")


#Exportation
#export(
#    TARGETS
#    ${EDITOR_NAME}
#    NAMESPACE ${EDITOR_NAME}::
#    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/Edit64Config.cmake"
#)


#target_sources(
    #${EDITOR_NAME}
    #PRIVATE

    #Directory.h
    #Parse.h
    
    #Directory.cpp
    #Parse.cpp
    #Main.cpp
#)

#target_link_libraries(
    #${EDITOR_NAME}
    #PUBLIC

    #Qt::Core
    #Qt::Widgets
    #Qt::Gui
    #Qt::OpenGL
    #${ENGINE_NAME}
#)

#qt_import_plugins(${EDITOR_NAME}
    #INCLUDE Qt5::QWindowsPlugin
#)

#target_include_directories(
    #${EDITOR_NAME}
    #PUBLIC

    #${Qt5Core_INCLUDE_DIRS}
    #${Qt5Widgets_INCLUDE_DIRS}
    #${Qt5Gui_INCLUDE_DIRS}
    #${Qt5OpenGL_INCLUDE_DIRS}
#)


if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::OpenGL> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)

add_subdirectory(QT)
