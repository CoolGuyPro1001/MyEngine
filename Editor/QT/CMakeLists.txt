set(
    EDITOR_UI
    mainwindow.ui
)

set(
    EDITOR_HEADERS
    mainwindow.h
    tree.h
    openglwidget.h
)

target_sources(
    ${EDITOR_NAME}
    PRIVATE

    mainwindow.h
    tree.h
    openglwidget.h

    mainwindow.cpp
    openglwidget.cpp
    tree.cpp

    mainwindow.ui
)