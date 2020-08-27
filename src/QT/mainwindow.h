#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Graphics/Graphics.h"
#include "Graphics/Camera.h"

#include <QMainWindow>
#include "openglwidget.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTreeWidgetItem>
#include <QFileSystemModel>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include <iostream>

namespace Ui
{
    class MainWindow : public QMainWindow 
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    protected:
        void keyPressEvent(QKeyEvent* e);
        void mousePressEvent(QMouseEvent* e);
        void mouseReleaseEvent(QMouseEvent* e);
        void mouseMoveEvent(QMouseEvent* e);

    private:
        void CreateActions();
        void CreateMenus();
        void OpenGame();

        OpenGLWidget *open_gl;
        Ui::Edit64* ui;
        QFileSystemModel* model;
        bool drag_screen;
        int mouse_x;
        int mouse_y;
        float sensitivity;

        QAction* new_file_action;
        QAction* new_game_action;
        QAction* new_mod_action;
        QAction* open_game_action;
        QAction* open_mod_action;
        QAction* game_directories_action;

        QMenu* file_menu;
        QMenu* edit_menu;
        QMenu* options_menu;
    };
}
#endif // MAINWINDOW_H
