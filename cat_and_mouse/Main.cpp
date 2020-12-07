#include "Cat.h"
#include "Mouse.h"

#include <Actor.h>
#include <Level.h>
#include <Controller.h>
#include <Shapes.h>
#include <Common/Units.h>
#include <Core/Load.h>
#include <Graphics/Camera.h>

#include <SDL2/SDL_keycode.h>

#include <string>
#include <vector>

int main()
{
    Shared<Model> box = Cube(1.0, Color(1.0, 1.0, 0, 1.0));

    Cat cat = Cat(box);
    cat.position = Vector3(0, 0, 0);
    cat.rotation = Vector3(0, 0, 0);
    cat.scale = Vector3(1.0, 1.0, 1.0);
    
    //Mouse mouse = Mouse(box);

    Graphics::Camera camera;

    Controller controller = Controller();
    controller.SetStickKeyboard("move", SDLK_w, SDLK_s, SDLK_d, SDLK_a);
    controller.BindStickX("move", cat, &Cat::OnRight);
    controller.BindStickY("move", cat, &Cat::OnUp);

    Level lvl = Level();
    lvl.actors.push_back(cat);
    lvl.cameras.push_back(camera);
    lvl.models.push_back(box);
    lvl.controllers.push_back(controller);

    std::string test = "test";
    
    std::cout.flush();

    Engine::Start(500, 500, "Cat And Mouse");
    Engine::LoadLevel(lvl);
    Engine::Run();

    return 0;
}