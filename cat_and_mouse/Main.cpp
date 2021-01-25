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
    //Textures
    Shared<Graphics::Texture> smile = CreateShared<Graphics::Texture>("../../res/smile.etex", 0);

    //Models
    Shared<Model> box = CreateShared<Model>("../../res/cube.emodel", smile);

    //Actors
    Shared<Cat> cat = CreateShared<Cat>(box);
    cat->position = Vector3(0, 0, 0);
    cat->rotation = Vector3(0, 0, 0);
    cat->scale = Vector3(1.0, 1.0, 1.0);
    cat->position_velocity = Vector3(0, 0, 0);

    //Shared<Mouse> mouse = CreateShared<Mouse>(box);
    //mouse->position = Vector3(0, 0, 0);
    //mouse->rotation = Vector3(0, 0, 0);
    //mouse->scale = Vector3(0.5, 0.5, 0.5);

    Graphics::Camera camera = Graphics::Camera();

    Controller controller = Controller();
    StickAction move;
    move.down_key = SDLK_s;
    move.up_key = SDLK_w;
    move.right_key = SDLK_d;
    move.left_key = SDLK_a;

    ButtonAction move_down;
    move_down.key = SDLK_q;

    ButtonAction move_up;
    move_up.key = SDLK_e;
    
    BindStickX(move, cat, &Cat::OnRight);
    BindStickY(move, cat, &Cat::OnForwards);
    BindButtonPress(move_up, cat, &Cat::OnUpPressed);
    BindButtonPress(move_down, cat, &Cat::OnDownPressed);
    BindButtonRelease(move_up, cat, &Cat::OnReleased);
    BindButtonRelease(move_down, cat, &Cat::OnReleased);

    controller.AddStickAction(move);
    controller.AddButtonAction(move_up);
    controller.AddButtonAction(move_down);

    Level lvl = Level();
    lvl.actors.push_back(cat);
    //lvl.actors.push_back(mouse);
    lvl.cameras.push_back(camera);
    lvl.models.push_back(box);
    lvl.textures.push_back(smile);
    lvl.controllers.push_back(controller);

    Engine::Start(500, 500, "Cat And Mouse");
    Engine::LoadLevel(lvl);
    Engine::Run();

    return 0;
}