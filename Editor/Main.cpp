//define GL headers before QT

#include <QApplication>
#include "QT/mainwindow.h"

#include <Common/Units.h>
#include <Graphics/IndexBuffer.h>
#include <Controller.h>

#include <thread>
#include <chrono>

#include "Parse.h"
#include "Directory.h"

#include <Actor.h>
#include <Core/Load.h>
#include <Core/Enviroment.h>
#include <Graphics/Camera.h>

int main(int argc, char* args[])
{
    QCoreApplication::addLibraryPath("./");
    QApplication app(argc, args);
    Ui::MainWindow main_window;
    main_window.show();
    
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
    //Level 
    Level lvl = Level(actors);
    lvl.cameras.push_back(camera);


    Engine::LoadLevel(lvl);
    
    bool running = true;
    std::thread engine(Run, std::ref(running), std::ref(main_window));
    int return_code = app.exec();

    running = false;
    engine.join();
    return return_code;
}