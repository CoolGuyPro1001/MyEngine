//define GL headers before QT

#include "Engine/Graphics/Graphics.h"

#include <QApplication>
#include "Editor/QT/mainwindow.h"

#include "Common/Units.h"
#include "Engine/Graphics/IndexBuffer.h"
#include "Engine/Controller.h"

#include <thread>
#include <chrono>

#include "Editor/Parse.h"
#include "Editor/Directory.h"

#include <Engine/Actor.h>
#include "Engine/Actor.h"
#include "Engine/Core/Load.h"
#include "Engine/Core/Enviroment.h"
#include "Engine/Graphics/Camera.h"

void Run(bool& running, Ui::MainWindow& main_window)
{
    TIME last_time;
    while(running)
    {
        TIME current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> delay = current_time - last_time;
        last_time = current_time;

        std::vector<std::function<void()>> ticks;
        Engine::AddTickFunction(ticks, )
        Engine::Tick(ticks);
    }
}

int main(int argc, char* args[])
{
    QCoreApplication::addLibraryPath("./");
    QApplication app(argc, args);
    Ui::MainWindow main_window;
    main_window.show();

    Graphics::UseShader("res/BaseShader.shader");
    Graphics::InitTransformUniform();
    
    //Vertices For The Model
    std::vector<Vertex> vertices = std::vector<Vertex>();
    vertices.push_back(Vertex(Vector3(-0.5, -0.5, 0), Color(1, 0, 0, 1)));
    vertices.push_back(Vertex(Vector3(0.5, -0.5, 0), Color(1, 0, 0, 1)));
    vertices.push_back(Vertex(Vector3(0.5, 0.5, 0), Color(1, 0, 0, 1)));
    vertices.push_back(Vertex(Vector3(-0.5, -0.5, 0), Color(1, 0, 0, 1)));
    vertices.push_back(Vertex(Vector3(-0.5, 0.5, 0), Color(1, 0, 0, 1)));
    vertices.push_back(Vertex(Vector3(0.5, 0.5, 0), Color(1, 0, 0, 1)));

    //Model
    Shared<Model> model = Parse::FileToModel("res/model.c");

    //Actor
    std::vector<Actor> actors = std::vector<Actor>();
    actors.push_back(Actor(model));
    actors[0].position = Vector3(0.0f, 0.0f, 0.0f);
    actors[0].rotation = Vector3(0.0f, 0.0f, 0.0f);
    actors[0].scale = Vector3(1.0f, 1.0f, 1.0f);

    //Camera
    Graphics::Camera camera = Graphics::Camera();

    //Controller
    Controller camera_controller = Controller();
    camera_controller.
    //Level 
    Level lvl = Level(actors);
    lvl.AddCamera(camera);


    Engine::LoadLevel(lvl);
    
    bool running = true;
    std::thread engine(Run, std::ref(running), std::ref(main_window));
    int return_code = app.exec();

    running = false;
    engine.join();
    return return_code;
}