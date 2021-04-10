#include "Cat.h"
#include "Mouse.h"

#include <Level.h>
#include <Actor.h>
#include <Controller.h>
#include <Shapes.h>
#include <Common/Units.h>
#include <Core/Entry.h>
#include <Graphics/Camera.h>

#include <SDL2/SDL_keycode.h>

#include <string>
#include <vector>

int main()
{
    //Textures
    Shared<Graphics::Texture> colors = Graphics::Texture::BMPToTexture("../../res/colors.bmp", 0);
    Shared<Graphics::Texture> sky = Graphics::Texture::BMPToTexture("../../res/sky.bmp", 1);
    Shared<Graphics::Texture> grass = Graphics::Texture::BMPToTexture("../../res/grass.bmp", 2);

    //Models
    Shared<Model> box = CreateShared<Model>("../../res/cube.emodel", colors);

    //Actors
    Shared<Cat> cat = CreateShared<Cat>(box);
    cat->position = Vector3(0, 0, 0);
    cat->rotation = Vector3(0, 0, 0);
    cat->scale = Vector3(1.0f, 1.0f, 1.0f);
    cat->position_velocity = Vector3(0, 0, 0);
    cat->can_fall = false;
    cat->CreateHitBox(2, 2, 2);

    Shared<Mouse> mouse = CreateShared<Mouse>(box);
    mouse->position = Vector3(5, 0, 0);
    mouse->rotation = Vector3(0, 0, 0);
    mouse->scale = Vector3(1.0f, 1.0f, 1.0f);
    mouse->position_velocity = Vector3(0, 0, 0);
    mouse->can_fall = false;
    mouse->CreateHitBox(2, 2, 2);

    Shared<Graphics::Camera> camera = CreateShared<Graphics::Camera>(50, false, 50);
    camera->forward_throttle = 0.0000001f;
    camera->sideways_throttle = 0.0000001f;
    camera->vertical_throttle = 0.0000001f;
    camera->pitch_throttle = 0.00000001f;
    camera->yaw_throttle = 0.00000001f;
    camera->roll_throttle = 0.00000001f;
    camera->rod_yaw_throttle = 0.00000001f;
    camera->rod_pitch_throttle = 0.00000001f;
    camera->fov = 70.0f;
    camera->AttachRod(cat, 10.0f, true);

    Controller controller = Controller();

    StickAction move;
    move.down_key = SDLK_s;
    move.up_key = SDLK_w;
    move.right_key = SDLK_d;
    move.left_key = SDLK_a;

    StickAction camera_rod;
    camera_rod.down_key = SDLK_k;
    camera_rod.up_key = SDLK_i;
    camera_rod.right_key = SDLK_l;
    camera_rod.left_key = SDLK_j;

    StickAction camera_vertical;
    camera_vertical.up_key = SDLK_o;
    camera_vertical.down_key = SDLK_u;
    
    StickAction camera_roll;
    camera_roll.left_key = SDLK_z;
    camera_roll.right_key = SDLK_x;

    StickAction camera_rotate;
    camera_rotate.up_key = SDLK_UP;
    camera_rotate.down_key = SDLK_DOWN;
    camera_rotate.right_key = SDLK_RIGHT;
    camera_rotate.left_key = SDLK_LEFT;

    ButtonAction move_down;
    move_down.key = SDLK_q;

    ButtonAction move_up;
    move_up.key = SDLK_e; 
    
    BindStickX(move, cat, &Cat::OnRight);
    BindStickY(move, cat, &Cat::OnForwards);
    BindStickX(camera_rod, camera, &Graphics::Camera::RodYaw);
    BindStickY(camera_rod, camera, &Graphics::Camera::RodPitch);
    BindStickY(camera_vertical, camera, &Graphics::Camera::MoveVertical);
    BindStickX(camera_roll, camera, &Graphics::Camera::Roll);
    BindStickX(camera_rotate, camera, &Graphics::Camera::Yaw);
    BindStickY(camera_rotate, camera, &Graphics::Camera::Pitch);
    BindButtonPress(move_up, cat, &Cat::OnUpPressed);
    BindButtonPress(move_down, cat, &Cat::OnDownPressed);
    BindButtonRelease(move_up, cat, &Cat::OnReleased);
    BindButtonRelease(move_down, cat, &Cat::OnReleased);

    controller.AddStickAction(move);
    controller.AddStickAction(camera_rod);
    controller.AddStickAction(camera_vertical);
    controller.AddStickAction(camera_roll);
    controller.AddStickAction(camera_rotate);
    controller.AddButtonAction(move_up);
    controller.AddButtonAction(move_down);

    Level lvl = Level();
    lvl.AddActor(mouse);
    lvl.sky_block = CreateShared<Model>("../../res/sky.emodel", sky);
    lvl.terrain = CreateShared<Model>("../../res/terrain.emodel", grass);
    //lvl.terrain->hitbox = CreateShared<HitBox>(Vector3(0, 0, 0), 200, 0, 200);
    lvl.gravity = -0.01;
    lvl.AddModel(box);
    lvl.AddActor(cat);
    lvl.AddCamera(camera);
    lvl.AddTexture(colors);
    lvl.AddTexture(sky);
    lvl.AddTexture(grass);
    lvl.AddController(controller);

    Engine::Start(500, 500, "Cat And Mouse");
    Engine::LoadLevel(lvl);
    Engine::Run(false);

    return 0;
}