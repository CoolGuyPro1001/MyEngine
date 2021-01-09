//define GL headers before QT

#include <QApplication>
#include "QT/mainwindow.h"
#include <iostream>

#include "Parse.h"
#include "Directory.h"

#include <Shapes.h>
#include <Actor.h>
#include <Graphics/Camera.h>
#include <Controller.h>
#include <Level.h>
#include <Core/Load.h>
#include <Graphics/Graphics.h>

int main(int argc, char** args)
{
    QCoreApplication::addLibraryPath("./");
    QApplication app(argc, args);
    Ui::MainWindow main_window;
    main_window.show();
    
    
    int return_code = app.exec();
    std::cin.get();
    return return_code;
}