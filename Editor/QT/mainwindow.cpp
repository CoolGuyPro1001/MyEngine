#include "mainwindow.h"

namespace Ui
{
    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Edit64)
    {
        ui->setupUi(this);

        open_gl = new OpenGLWidget(this);
        setCentralWidget(open_gl);
        setFocusPolicy(Qt::StrongFocus);
        drag_screen = false;
        mouse_x = 0;
        mouse_y = 0;
        sensitivity = 0.005f;

        model = new QFileSystemModel;
        model->setReadOnly(false);
        ui->treeView->setModel(model);

        CreateActions();
        CreateMenus();
    }



    MainWindow::~MainWindow()
    {
        delete ui;
        delete model;
        delete new_file_action;
        delete new_game_action;
        delete new_mod_action;
        delete open_game_action;
        delete open_mod_action;

    }

    void MainWindow::CreateActions()
    {
        new_file_action = new QAction(tr("&New File"), this);
        new_file_action->setShortcuts(QKeySequence::New);
        new_file_action->setStatusTip(tr("Create A New File"));
        //connect(new_action, &QAction::triggered, this, @MainWindow::)

        new_game_action = new QAction(tr("&New Game"), this);
        new_game_action->setStatusTip(tr("Create A New Game Project"));

        new_mod_action = new QAction(tr("&New Mod"), this);
        new_mod_action->setStatusTip(tr("Create A New Mod Project"));

        open_game_action = new QAction(tr("&Open Game"), this);
        open_game_action->setStatusTip(tr("Open A Game Project"));
        connect(open_game_action, &QAction::triggered, this, &MainWindow::OpenGame);

        open_mod_action = new QAction(tr("&Open Mod"), this);
        open_mod_action->setStatusTip(tr("Open A Mod Project"));

        game_directories_action = new QAction(tr("&Game Directories"));
        game_directories_action->setStatusTip(tr("Configure Directories For 64 Games"));
    }

    void MainWindow::OpenGame()
    {
        QString game_directory = QFileDialog::getExistingDirectory(this, tr("Open Game"), "C:\\");
        model->setRootPath(game_directory);
        ui->treeView->setModel(model);
        ui->treeView->update();
    }

    void MainWindow::CreateMenus()
    {
        file_menu = menuBar()->addMenu(tr("&File"));
        file_menu->addAction(new_file_action);
        file_menu->addSeparator();
        file_menu->addAction(new_game_action);
        file_menu->addAction(new_mod_action);
        file_menu->addSeparator();
        file_menu->addAction(open_game_action);
        file_menu->addAction(open_mod_action);

        edit_menu = menuBar()->addMenu(tr("&Edit"));

        options_menu = menuBar()->addMenu(tr("&Options"));
        options_menu->addAction(game_directories_action);
    }

    void MainWindow::keyPressEvent(QKeyEvent* e)
    {
    }

    void MainWindow::mousePressEvent(QMouseEvent* e)
    {
        drag_screen = true;
        mouse_x = e->x();
        mouse_y = e->y();
    }

    void MainWindow::mouseReleaseEvent(QMouseEvent* e)
    {
        drag_screen = false;
    }

    void MainWindow::mouseMoveEvent(QMouseEvent* e)
    {
        if(!Graphics::initialized || !drag_screen)
        {
            return;
        }

        Graphics::camera.TurnCameraY(sensitivity * (e->x() - mouse_x));
        Graphics::camera.TurnCameraP(-sensitivity * (e->y() - mouse_y));

        //Graphics::camera.PrintCameraLocation();

        mouse_x = e->x();
        mouse_y = e->y();

        UpdateView();
    }

    void MainWindow::UpdateView()
    {
        open_gl->update();
    }
}