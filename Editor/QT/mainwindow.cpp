#include "mainwindow.h"
#include <QLineEdit>

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

        ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::ExplorerContextMenu);
        model = new QFileSystemModel;
        model->setReadOnly(false);
        CreateActions();
        CreateMenus(); 
    }



    MainWindow::~MainWindow()
    {
        delete ui;
        delete model;
        delete new_file_action;
        delete new_game_action;
        //delete new_mod_action;
        delete open_game_action;
        //delete open_mod_action;
        delete new_folder_action;
        delete new_source_action;
        delete new_header_action;
        delete new_level_action;
        delete new_model_action;
        delete new_texture_action;
        delete remove_folder_action;
        delete remove_file_action;
    } 

    void MainWindow::CreateActions()
    {
        new_file_action = new QAction(tr("&New File"), this);
        new_file_action->setShortcuts(QKeySequence::New);
        new_file_action->setStatusTip(tr("Create A New File"));
        //connect(new_action, &QAction::triggered, this, @MainWindow::)

        new_game_action = new QAction(tr("&New Game"), this);
        new_game_action->setStatusTip(tr("Create A New Game Project"));

        //new_mod_action = new QAction(tr("&New Mod"), this);
        //new_mod_action->setStatusTip(tr("Create A New Mod Project"));

        open_game_action = new QAction(tr("&Open Game"), this);
        open_game_action->setStatusTip(tr("Open A Game Project"));
        connect(open_game_action, &QAction::triggered, this, &MainWindow::OpenGame);

        //open_mod_action = new QAction(tr("&Open Mod"), this);
        //open_mod_action->setStatusTip(tr("Open A Mod Project"));

        //game_directories_action = new QAction(tr("&Game Directories"));
        //game_directories_action->setStatusTip(tr("Configure Directories For 64 Games"));

        new_folder_action = new QAction(tr("New Folder"), this);
        new_source_action = new QAction(tr("New C++ Source File"), this);
        new_header_action = new QAction(tr("New Header File"), this);
        new_level_action = new QAction(tr("New Level File"), this);
        new_model_action = new QAction(tr("New Model File"), this);
        new_texture_action = new QAction(tr("New Texture File"), this);

        remove_folder_action = new QAction(tr("Remove Folder"), this);
        remove_file_action = new QAction(tr("Remove File"), this);
    }

    void MainWindow::OpenGame()
    {
        QString game_directory = QFileDialog::getExistingDirectory(this, tr("Open Game"), "C:\\");
        std::string f = game_directory.toStdString();
        QModelIndex root = model->setRootPath(game_directory);
        ui->treeView->setModel(model);
        ui->treeView->setRootIndex(root);

        for(int i = 1; i < model->columnCount(); i++)
        {
            ui->treeView->hideColumn(i);
        }
        ui->treeView->update();
    }

    void MainWindow::CreateMenus()
    {
        file_menu = menuBar()->addMenu(tr("&File"));
        file_menu->addAction(new_file_action);
        file_menu->addSeparator();
        file_menu->addAction(new_game_action);
        //file_menu->addAction(new_mod_action);
        file_menu->addSeparator();
        file_menu->addAction(open_game_action);
        //file_menu->addAction(open_mod_action);

        edit_menu = menuBar()->addMenu(tr("&Edit"));

        options_menu = menuBar()->addMenu(tr("&Options"));
        //options_menu->addAction(game_directories_action);
    }

    void MainWindow::ExplorerContextMenu(const QPoint& point)
    {
        explorer_menu_point = point;

        QMenu context_menu = QMenu(this);
        QModelIndex selected_index = ui->treeView->indexAt(explorer_menu_point);
        if(model->hasChildren(selected_index))
        {
            connect(new_folder_action, &QAction::triggered, this, &MainWindow::CreateFolder);
            connect(new_source_action, &QAction::triggered, this, &MainWindow::NewFile);
            connect(new_header_action, &QAction::triggered, this, &MainWindow::NewFile);
            connect(new_level_action, &QAction::triggered, this, &MainWindow::NewFile);
            connect(new_model_action, &QAction::triggered, this, &MainWindow::NewFile);
            connect(new_texture_action, &QAction::triggered, this, &MainWindow::NewFile);
            connect(remove_folder_action, &QAction::triggered, this, &MainWindow::RemoveFolder);

            context_menu.addAction(new_folder_action);
            context_menu.addAction(new_source_action);
            context_menu.addAction(new_header_action);
            context_menu.addSeparator();
            context_menu.addAction(new_level_action);
            context_menu.addAction(new_model_action);
            context_menu.addAction(new_texture_action);
            context_menu.addSeparator();
            context_menu.addAction(remove_folder_action);
        }
        else
        {
            connect(remove_file_action, &QAction::triggered, this, &MainWindow::RemoveFile);
            context_menu.addAction(remove_file_action);
        }

        context_menu.exec(ui->treeView->mapToGlobal(point));
    }

    void MainWindow::CreateFolder()
    {
        QModelIndex index = ui->treeView->indexAt(explorer_menu_point);
        QDir(model->filePath(index)).mkdir(tr("Awesome Folder"));
    }

    void MainWindow::RemoveFolder()
    {
        QModelIndex index = ui->treeView->indexAt(explorer_menu_point);
        QDir dir = QDir(model->filePath(index));
        dir.removeRecursively();
    }

    void MainWindow::NewFile()
    {
        QAction* obj = (QAction*) sender();
        QModelIndex index = ui->treeView->indexAt(explorer_menu_point);
        QDir::setCurrent(model->filePath(index));
        std::string m = model->filePath(index).toStdString();
        QFile file("awesome_file");

        if(obj == new_source_action)
        {
            file.setFileName(tr("awesome_cpp.cpp"));
        }
        else if(obj == new_header_action)
        {
            file.setFileName(tr("awesome_header.h"));
        }
        else if(obj == new_level_action)
        {
            file.setFileName(tr("awesome_level.elvl"));
        }
        else if(obj == new_model_action)
        {
            file.setFileName(tr("awesome_model.emodel"));
        }
        else if(obj == new_texture_action)
        {
            file.setFileName(tr("awesome_texture.etex"));
        }

        file.open(QIODevice::ReadWrite);
    }

    void MainWindow::RemoveFile()
    {
        QModelIndex index = ui->treeView->indexAt(explorer_menu_point);
        QFile::moveToTrash(model->filePath(index));
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
        //if(!Graphics::initialized || !drag_screen)
        //{
        //    return;
        //}

        //Camera.TurnCameraY(sensitivity * (e->x() - mouse_x));
        //Camera.TurnCameraP(-sensitivity * (e->y() - mouse_y));

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

#include "moc_mainwindow.cpp"