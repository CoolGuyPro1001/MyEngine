//define GL headers before QT

#include "Engine/Graphics/Graphics.h"

#include <QApplication>
#include "Editor/QT/mainwindow.h"

#include "Engine/Graphics/Units.h"
#include "Engine/Graphics/IndexBuffer.h"


#include <memory>
#include <vector>
#include <iostream>
#include <chrono>

#include "Editor/Parse.h"
#include "Editor/Directory.h"

#include "Defines.h"

int main(int argc, char* args[])
{
    bool running = true;
    TIME last_time;
    while(running)
    {
        TIME current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> delay = current_time - last_time;
        last_time = current_time;

        
    }

    /*std::cout << &Graphics::camera << "\n";
    QCoreApplication::addLibraryPath("./");
    QApplication app(argc, args);

    Ui::MainWindow mainwindow;

    mainwindow.show();
    Graphics::UseShader("res/BaseShader.shader");
    Graphics::InitMVP();
    std::shared_ptr<Graphics::VertexBuffer> vbo = Parse::FileToVbo("res/model.c");
    Graphics::AddBuffer(vbo.get());
    return app.exec();*/
}
