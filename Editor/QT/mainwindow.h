#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

        void UpdateView();
        uint& GetGraphicsBuffer();
        uint& GetGraphicsVao();

    protected:
        void keyPressEvent(QKeyEvent* e);
        void mousePressEvent(QMouseEvent* e);
        void mouseReleaseEvent(QMouseEvent* e);
        void mouseMoveEvent(QMouseEvent* e);

    private:
        void CreateActions();
        void CreateMenus();
        void OpenGame();
        void ExplorerContextMenu(const QPoint& point);
        void CreateFolder();
        void NewFile();
        void RenameFolder();
        void RenameFile();
        void RemoveFolder();
        void RemoveFile();

        OpenGLWidget *open_gl;
        Ui::Edit64* ui;
        QFileSystemModel* model;
        bool drag_screen;
        int mouse_x;
        int mouse_y;
        float sensitivity;
        QPoint explorer_menu_point;

        QAction* new_file_action;
        QAction* new_game_action;
        QAction* new_mod_action;
        QAction* open_game_action;
        QAction* open_mod_action;
        QAction* game_directories_action;

        QAction* new_folder_action;
        QAction* new_source_action;
        QAction* new_header_action;
        QAction* new_level_action;
        QAction* new_model_action;
        QAction* new_texture_action;
        QAction* remove_folder_action;
        QAction* remove_file_action;

        QMenu* file_menu;
        QMenu* edit_menu;
        QMenu* options_menu;
    };
}
#endif
