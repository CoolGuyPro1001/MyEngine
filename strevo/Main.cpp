#include "Strevo.h"
//#include "Sword.h"

#include <Core/Entry.h>

#include <Level.h>
#include <Actor.h>

#include <Events/InputEvents.h>

#include <Components/CameraComponent.h>
#include <Components/ModelComponent.h>
#include <Components/CollisionComponent.h>

#include <Core/Media/InputMedia.h>
#include <Core/MediaDevices/InputDevice.h>
#include <Core/Media/InputCodes.h>
#include <Core/MediaBackends/SDL/SDLInput.h>

#include <Core/Media/WindowMedia.h>
#include <Core/MediaBackends/SDL/SDLWindow.h>

#include <Core/Media/GraphicsMedia.h>
#include <Core/MediaBackends/OpenGL/OGLGraphics.h>

#include <Core/Media/Graphics/GraphicsBuffer.h>

#include <Core/Time.h>

#include <Core/Media/Graphics/Texture.h>

/*
 * This File Is A Demo Game Used For Debugging And Performance Testing
 * Some Disabled Features Are Commented Out
 */

void SpawnActors(int amount, Level& lvl, Shared<CModel> model)
{
    std::vector<Shared<Strevo>> army(amount);
    int i = 0;
    int x = 0;
    int y = 0;
    int z = 0;

    while(i < army.size())
    {
        army[i] = CreateShared<Strevo>(Vector3(x, y, z));
        army[i]->AddComponent<CModel>(model);

        x += 4;
        if(x >= 48)
        {
            z += 4;
            x = 0;

            if(z >= 48)
            {
                y += 4;
                z = 0;
            }
        }

        lvl.AddActor(army[i]);
        i++;
    }
}

int main()
{
    //AddFont("../../res/comic.ttf", "../../res/comicbd.ttf", "../../res/comici.ttf", "../../res/comicz.ttf", 0, 48);

    std::vector<Shared<ModelTexture>> textures = LoadTextureFile("../../res/textures.bmp", 512);
    Level lvl = Level();

    //CModels
    Shared<CModel> box = lvl.CreateComponent<CModel>("../../res/cube.emodel", std::vector{textures[1]});
    Shared<CModel> grass = lvl.CreateComponent<CModel>("../../res/terrain.emodel", std::vector{textures[2]});

    Shared<CCamera> camera = lvl.CreateComponent<CCamera>(50, false, 1000);
    camera->forward_throttle = 50.0f;
    camera->sideways_throttle = 50.0f;
    camera->vertical_throttle = 0.000001f;
    camera->pitch_throttle = 50.0f;
    camera->yaw_throttle = 50.0f;
    camera->roll_throttle = 0.0000001f;
    camera->rod_yaw_throttle = -90.0f;
    camera->rod_pitch_throttle = 90.0f;
    camera->zoom_throttle = 0.00001f;
    camera->view_throttle = 0.000001f;
    camera->rod_length_throttle = 0.0000001f;
    camera->fov = 70.0f;
    //camera->position = Vector3(0, 0, -20);

    Shared<Strevo> strevo = CreateShared<Strevo>();
    strevo->AddComponent<CCamera>(camera);
    strevo->AddComponent<CModel>(box);
    strevo->AddComponent<CCollision>(lvl.CreateComponent<CCollision>(2, 2, 2));
    strevo->rotation = Vector3(0, 90, 0);

    Shared<Strevo> sword = CreateShared<Strevo>();
    sword->position = Vector3(0, 0, 10);
    sword->AddComponent<CModel>(box);
    sword->AddComponent<CCollision>(lvl.CreateComponent<CCollision>(2, 2, 2));

    Shared<Actor> terrain = CreateShared<Actor>();
    terrain->AddComponent<CModel>(grass);
    terrain->enable_tick = false;

    camera->AttachRod(strevo, 10.0f, Vector3(0, 0, 0), true);

    Unique<MInput> input = CreateUnique<SDLInput>();
    Shared<InputDevice> keyboard = input->GetInputDevice(KEYBOARD_DEVICE);

    Shared<InputDevice> gamepad = input->GetInputDevice(GAMEPAD_DEVICE, 1);

    if(gamepad)
    {
        gamepad->deadzone_radius = 0.5f;
    }

    keyboard->BindButton(KEY_W, strevo, &Strevo::OnKeyForward);
    keyboard->BindButton(KEY_S, strevo, &Strevo::OnKeyBack);
    keyboard->BindButton(KEY_A, strevo, &Strevo::OnKeyLeft);
    keyboard->BindButton(KEY_D, strevo, &Strevo::OnKeyRight);

    //keyboard->BindButton(KEY_W, camera, &CCamera::MoveForwards);
    //keyboard->BindButton(KEY_S, camera, &CCamera::MoveBackwards);
    //keyboard->BindButton(KEY_A, camera, &CCamera::MoveLeft);
    //keyboard->BindButton(KEY_D, camera, &CCamera::MoveRight);

    /*device->BindButton(KEY_ARROW_UP,    camera, &CCamera::RodPitchUp);
    device->BindButton(KEY_ARROW_DOWN,  camera, &CCamera::RodPitchDown);
    device->BindButton(KEY_ARROW_LEFT,  camera, &CCamera::RodYawLeft);
    device->BindButton(KEY_ARROW_RIGHT, camera, &CCamera::RodYawRight);*/

    Shared<InputDevice> mouse = input->GetInputDevice(MOUSE_DEVICE);
    mouse->BindAnalog(MOUSE_X, camera, &CCamera::RodYaw);
    mouse->BindAnalog(MOUSE_Y, camera, &CCamera::RodPitch);

    //Fonts
    /*Shared<Widget> = CreateShared<Widget>;
    widget->position = Vector2(-0.5f, 0);
    widget->z_depth = 0.5f;
    widget->size = Vector2(0.1f, 0.1f);
    widget->color = Color(0xff, 0x00, 0x00, 0xff);
    widget->texture = strevo_tex;

    Shared<GText> text = widget->CreateComponent<GText>();
    text->string = "ABC";
    text->font = GetFont("comic");
    text->color = Color(0xff, 0x00, 0xff, 0x01);
    text->scale = 2.0f;
    text->z_depth = 0.4f;
    text->line_spacing = 1.0f;
    text->horizontal_alignment = TextAlignHorizontal::LEFT
    text->vertical_alignment = TextAlignVertical::BOTTOM;
    text->word_wrap = false;
    text->text_style = TextStyle::REGULAR;*/

    //lvl.gravity = -0.05f;

    lvl.AddActor(strevo);
    lvl.model_textures = textures;
    lvl.AddActor(sword);
    lvl.AddActor(terrain);

    Unique<MWindow> window = CreateUnique<SDLWindow>(500, 500, "Strevo", false);
    Unique<MRenderer> renderer = CreateUnique<OGLRenderer>(*window);

    Start(std::move(window), std::move(renderer), std::move(input), lvl);
}
