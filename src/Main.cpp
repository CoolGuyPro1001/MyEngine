//define GL headers before QT

#include "Engine/Graphics/Graphics.h"

#include <QApplication>
#include "Editor/QT/mainwindow.h"

#include "Common/Units.h"
#include "Engine/Graphics/IndexBuffer.h"


#include <memory>
#include <vector>
#include <iostream>
#include <chrono>

#include "Editor/Parse.h"
#include "Editor/Directory.h"

#include "Engine/Level.h"
#include "Engine/Actor.h"

#include "pch.h"

int main(int argc, char* args[])
{
    QCoreApplication::addLibraryPath("./");
    QApplication app(argc, args);
    Ui::MainWindow mainwindow;
    mainwindow.show();

    Graphics::UseShader("res/BaseShader.shader");
    Graphics::InitMVP();
    
    bool running = true;
    TIME last_time;
    while(running)
    {
        TIME current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> delay = current_time - last_time;
        last_time = current_time;

    }
    
    return app.exec();
}
