//define GL headers before QT

#include "Engine/Graphics/Graphics.h"

#include <QApplication>
#include "Editor/QT/mainwindow.h"

#include "Engine/Graphics/Units.h"
#include "Engine/Graphics/IndexBuffer.h"


#include <memory>
#include <vector>
#include <iostream>

#include "Editor/Parse.h"
#include "Editor/Directory.h"

int main(int argc, char* args[])
{
    std::cout << &Graphics::camera << "\n";
    QCoreApplication::addLibraryPath("./");
    QApplication app(argc, args);

    Ui::MainWindow mainwindow;

    mainwindow.show();
    Graphics::UseShader("res/BaseShader.shader");
    Graphics::InitMVP();
    std::shared_ptr<Graphics::VertexBuffer> vbo = Parse::FileToVbo("res/model.c");
    Graphics::AddBuffer(vbo.get());
    return app.exec();
}