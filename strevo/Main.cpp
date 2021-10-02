#include "Strevo.h"
#include "Sword.h"

#include <Level.h>
#include <Actor.h>
#include <Component.h>
#include <Controller.h>
#include <Shapes.h>
#include <Common/Vector3.h>
#include <Core/Entry.h>
#include <Graphics/Camera.h>
#include <GUI/GUI.h>
#include <GUI/Text.h>

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

void FreeCam(Shared<Controller> player, Shared<Controller> camera)
{
    player->enabled = !player->enabled;
    camera->enabled = !camera->enabled;
};

int main()
{
    Texture::width = 512;
    Texture::height = 512;
    
    AddFont("../../res/comic.ttf", "../../res/comicbd.ttf", "../../res/comici.ttf", "../../res/comicz.ttf", 0, 48);
    
    Level lvl = Level();

    //Textures
    Shared<Texture> strevo_tex = Texture::BMPToTexture("../../res/strevo.bmp");
    Shared<Texture> sky = Texture::BMPToTexture("../../res/sky.bmp");
    Shared<Texture> grass = Texture::BMPToTexture("../../res/grass.bmp");

    //Models
    Shared<Model> box = CreateShared<Model>("../../res/cube.emodel", std::vector{strevo_tex});

    Shared<Camera> camera = CreateShared<Camera>(50, false, 50);
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
    strevo->SetPosition(0, 1, 0);
    strevo->CreateHitBox(2, 2, 2);

    Shared<Strevo> strebro = CreateShared<Strevo>(box, camera);
    strebro->SetPosition(0, 1, 5);
    strebro->CreateHitBox(2, 2, 2);

    //Components
    Shared<Sword> sword = CreateShared<Sword>(box, strevo);
    sword->SetRelativePosition(2.0f, 0, 0);
    strevo->AddComponent(sword);

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
    BindStickX(camera_rod, camera, &Camera::RodYaw);
    BindStickY(camera_rod, camera, &Camera::RodPitch);
    BindStickY(camera_vertical, camera, &Camera::MoveVertical);
    BindStickX(camera_roll, camera, &Camera::Roll);
    BindStickX(camera_rotate, camera, &Camera::Yaw);
    BindStickY(camera_rotate, camera, &Camera::Pitch);
    BindButtonPress(jump, strevo, &Strevo::OnJumpPressed);
    BindButtonRelease(jump, strevo, &Strevo::OnJumpReleased);
    BindButtonPress(free_cam, camera, &Camera::ToggleFreeCam);
    BindButtonPress(free_cam, &FreeCam, player_control, camera_control);
    BindStickX(camera_move, camera, &Camera::MoveSideways);
    BindStickY(camera_move, camera, &Camera::MoveDirectly);
    BindStickX(zoom_view, camera, &Camera::View);
    BindStickY(zoom_view, camera, &Camera::Zoom);
    BindStickY(rod_length, camera, &Camera::RodDistance);

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

    //Fonts

    //Widgets
    uint test_widget = GUI::CreateWidget();
    GUI::SetWidgetPosition(test_widget, -0.5, 0);
    GUI::SetWidgetZDepth(test_widget, 0.5f);
    GUI::SetWidgetSize(test_widget, Vector2(0.1f, 0.1f));
    GUI::SetWidgetColor(test_widget, 0xff, 0x00, 0x00, 0xff);
    GUI::SetWidgetTexture(test_widget, strevo_tex);
    GUI::SetWidgetText(test_widget, "Text");
    GUI::SetWidgetFont(test_widget, GetFont("comic"));
    GUI::SetWidgetTextColor(test_widget, 0xff, 0xff, 0, 0xff);
    GUI::SetWidgetTextScale(test_widget, 1.0f);
    GUI::SetWidgetTextZDepth(test_widget, 0.4f);
    GUI::SetWidgetLineSpacing(test_widget, 1.0f);
    GUI::SetWidgetHorizontalAlignment(test_widget, TextAlignHorizontal::LEFT);
    GUI::SetWidgetVerticalAllignment(test_widget, TextAlignVertical::BOTTOM);
    GUI::SetWidgetWordWrap(test_widget, false);
    GUI::SetWidgetTextStyle(test_widget, TextStyle::REGULAR);

    uint other_widget = GUI::CopyWidget(test_widget);
    GUI::SetWidgetZDepth(other_widget, 0.4f);
    GUI::SetWidgetTextZDepth(other_widget, 0.1f);
    GUI::SetWidgetPosition(other_widget, 0.5f, 0);

    lvl.sky_block = CreateShared<Object>(CreateShared<Model>("../../res/sky.emodel", std::vector{sky}));
    lvl.sky_block->locked = true;
    lvl.terrain = CreateShared<Object>(CreateShared<Model>("../../res/terrain.emodel", std::vector{grass}));
    lvl.terrain->locked = true;
    lvl.gravity = -0.05f;

    lvl.models = {box};
    lvl.actors = {strevo, strebro};
    lvl.cameras = {camera};
    lvl.textures = {strevo_tex, sky, grass};
    lvl.controllers = {player_control, camera_control};

    Start(500, 500, "Strevo");
    lvl.flat_collisions = ReadCollisionFile("../../res/landcollision.ecol");
    StartLevel(lvl);

    return 0;
}