#include "Strevo.h"

#include <Level.h>
#include <Actor.h>
#include <Controller.h>
#include <Shapes.h>
#include <Common/Units.h>
#include <Core/Entry.h>
#include <Graphics/Camera.h>

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

#include <string>
#include <vector>

void FreeCam(Shared<Controller> player, Shared<Controller> camera)
{
    player->enabled = !player->enabled;
    camera->enabled = !camera->enabled;
};

int main()
{
    //Textures
    Shared<Graphics::Texture> colors = Graphics::Texture::BMPToTexture("../../res/strevo.bmp", 0);
    Shared<Graphics::Texture> sky = Graphics::Texture::BMPToTexture("../../res/sky.bmp", 1);
    Shared<Graphics::Texture> grass = Graphics::Texture::BMPToTexture("../../res/grass.bmp", 2);

    //Models
    Shared<Model> box = CreateShared<Model>("../../res/cube.emodel", colors);

    Shared<Graphics::Camera> camera = CreateShared<Graphics::Camera>(50, false, 50);
    camera->forward_throttle = 0.000001f;
    camera->sideways_throttle = 0.000001f;
    camera->vertical_throttle = 0.000001f;
    camera->pitch_throttle = 0.0000001f;
    camera->yaw_throttle = 0.0000001f;
    camera->roll_throttle = 0.0000001f;
    camera->rod_yaw_throttle = -0.00000005f;
    camera->rod_pitch_throttle = -0.00000005f;
    camera->zoom_throttle = 0.00001f;
    camera->view_throttle = 0.000001f;
    camera->rod_length_throttle = 0.0000001f;
    camera->fov = 70.0f;

    //Actors
    Shared<Strevo> strevo = CreateShared<Strevo>(box, camera);
    strevo->position = Vector3(0, 1.01f, 0);
    strevo->rotation = Vector3(0, 0, 0);
    strevo->scale = Vector3(1.0f, 1.0f, 1.0f);
    strevo->position_velocity = Vector3(0, 0, 0);
    strevo->can_fall = false;
    strevo->CreateHitBox(2, 2, 2);

    camera->AttachRod(strevo, 10.0f, Vector3(0, -PI / 2, 0), true);

    Shared<Controller> player_control = CreateShared<Controller>();
    Shared<Controller> camera_control = CreateShared<Controller>();

    StickAction move;
    move.down_key = SDLK_s;
    move.up_key = SDLK_w;
    move.right_key = SDLK_d;
    move.left_key = SDLK_a;
    move.x_axis = SDL_CONTROLLER_AXIS_LEFTX;
    move.y_axis = SDL_CONTROLLER_AXIS_LEFTY;

    StickAction camera_rod;
    camera_rod.down_key = SDLK_k;
    camera_rod.up_key = SDLK_i;
    camera_rod.right_key = SDLK_l;
    camera_rod.left_key = SDLK_j;
    camera_rod.x_axis = SDL_CONTROLLER_AXIS_RIGHTX;
    camera_rod.y_axis = SDL_CONTROLLER_AXIS_RIGHTY;

    StickAction camera_vertical;
    camera_vertical.up_key = SDLK_o;
    camera_vertical.down_key = SDLK_u;
    
    StickAction camera_roll;
    camera_roll.left_key = SDLK_z;
    camera_roll.right_key = SDLK_x;

    StickAction camera_rotate;
    camera_rotate.x_axis = SDL_CONTROLLER_AXIS_RIGHTX;
    camera_rotate.y_axis = SDL_CONTROLLER_AXIS_RIGHTY;

    StickAction camera_move;
    camera_move.up_key = SDLK_w;
    camera_move.down_key = SDLK_s;
    camera_move.right_key = SDLK_d;
    camera_move.left_key = SDLK_a;
    camera_move.x_axis = SDL_CONTROLLER_AXIS_LEFTX;
    camera_move.y_axis = SDL_CONTROLLER_AXIS_LEFTY;

    ButtonAction jump;
    jump.button = SDL_CONTROLLER_BUTTON_A;

    ButtonAction free_cam;
    //free_cam.mouse_button = SDL_BUTTON_LEFT;
    free_cam.button = SDL_CONTROLLER_BUTTON_B;
    free_cam.key = SDLK_e;

    StickAction zoom_view;
    zoom_view.up_key = SDLK_UP;
    zoom_view.down_key = SDLK_DOWN;
    zoom_view.right_key = SDLK_RIGHT;
    zoom_view.left_key = SDLK_LEFT;
    zoom_view.right_button = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
    zoom_view.left_button = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;

    StickAction rod_length;
    rod_length.up_key = SDLK_o;
    rod_length.down_key = SDLK_u;
    rod_length.up_button = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
    rod_length.down_button = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
    
    BindStickX(move, strevo, &Strevo::OnRight);
    BindStickY(move, strevo, &Strevo::OnForwards);
    BindStickX(camera_rod, camera, &Graphics::Camera::RodYaw);
    BindStickY(camera_rod, camera, &Graphics::Camera::RodPitch);
    BindStickY(camera_vertical, camera, &Graphics::Camera::MoveVertical);
    BindStickX(camera_roll, camera, &Graphics::Camera::Roll);
    BindStickX(camera_rotate, camera, &Graphics::Camera::Yaw);
    BindStickY(camera_rotate, camera, &Graphics::Camera::Pitch);
    BindButtonPress(jump, strevo, &Strevo::OnJumpPressed);
    BindButtonRelease(jump, strevo, &Strevo::OnJumpReleased);
    BindButtonPress(free_cam, camera, &Graphics::Camera::ToggleFreeCam);
    BindButtonPress(free_cam, &FreeCam, player_control, camera_control);
    BindStickX(camera_move, camera, &Graphics::Camera::MoveSideways);
    BindStickY(camera_move, camera, &Graphics::Camera::MoveDirectly);
    BindStickX(zoom_view, camera, &Graphics::Camera::View);
    BindStickY(zoom_view, camera, &Graphics::Camera::Zoom);
    BindStickY(rod_length, camera, &Graphics::Camera::RodDistance);

    player_control->AddStickAction(move);
    player_control->AddStickAction(camera_rod);
    player_control->AddButtonAction(jump);
    player_control->AddStickAction(rod_length );
    player_control->AddButtonAction(free_cam);
    player_control->id = 0;
    
    camera_control->AddStickAction(camera_vertical);
    camera_control->AddStickAction(camera_roll);
    camera_control->AddStickAction(camera_rotate);
    camera_control->AddStickAction(camera_move);
    camera_control->AddStickAction(zoom_view);
    camera_control->AddButtonAction(free_cam);
    camera_control->id = 0;

    player_control->enabled = true;
    camera_control->enabled = false;

    Level lvl = Level();
    lvl.sky_block = CreateShared<Model>("../../res/sky.emodel", sky);
    lvl.terrain = CreateShared<Model>("../../res/terrain.emodel", grass);
    lvl.gravity = -0.001f;
    lvl.AddModel(box);
    lvl.AddActor(strevo);
    lvl.AddCamera(camera);
    lvl.AddTexture(colors);
    lvl.AddTexture(sky);
    lvl.AddTexture(grass);
    lvl.AddController(player_control);
    lvl.AddController(camera_control);
    lvl.ReadCollisionFile("../../res/landcollision.ecol");

    Engine::Start(500, 500, "Strevo");
    Engine::LoadLevel(lvl);
    Engine::Run(false);

    return 0;
}