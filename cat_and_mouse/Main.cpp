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

    Shared<Cat> cat = CreateShared<Cat>(box);
    cat->position = Vector3(0, 0, 0);
    cat->rotation = Vector3(0, 0, 0);
    cat->scale = Vector3(1.0, 1.0, 1.0);
    
    //Mouse mouse = Mouse(box);

    Graphics::Camera camera;

    Controller controller = Controller();
    StickAction move;
    move.down_key = SDLK_s;
    move.up_key = SDLK_w;
    move.right_key = SDLK_d;
    move.left_key = SDLK_a;
    
    BindStickX(move, cat, &Cat::OnRight);
    BindStickY(move, cat, &Cat::OnUp);
    controller.AddStickAction(move);

    Level lvl = Level();
    lvl.actors.push_back(cat);
    lvl.cameras.push_back(camera);
    lvl.models.push_back(box);
    lvl.controllers.push_back(controller);

    Engine::Start(500, 500, "Cat And Mouse");
    Engine::LoadLevel(lvl);
    Engine::Run();

    return 0;
}