# Creating A Game
Admit it, you went to this page first, didn't you?

Well then, let's create a game!

## Configuration
Before programming the game, choose parts of the Engine you'll want to use. These can be enabled or disabled any time. You'll need CMake.

Configurations can be found in the CMake Cache. To view the cache, use either CMakeGUI or the CMake configuration settings provided by your IDE.

You'll see different options. For this tutorial, select the ENABLE_RENDERING, ENABLE_TEXTURES, and ENABLE_INPUT options . Leave the other options unchecked.

Configure CMake to apply the changes. You'll notice additional cache variables have been created. These variables depend on what platform you are developing on.

### CH LAST
The engine will use Direct3D and XInput, which are already included in Windows

### MacOS/Linux
The engine will use OpenGL and SDL. Download the SDL2, GLEW, and GLM libraries. Set each directory in the CMake Cache to the corresponding cmake folder of each library.

## Creating CMakeLists.txt
Create a CMakeLists.txt file and copy the following.

~~~~~~~~~~~~~~~~~~~~~~~~~~~
project(Edit64 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

set(GAME [Game Name])
find_package(Engine64 REQUIRED)

add_executable(
    ${GAME}
    Main.cpp
    [Add Header and Source Files. One per line]
)

target_link_libraries(
    ${GAME}
    PUBLIC
    ${ENGINE_NAME}
)
~~~~~~~~~~~~~~~~~~~~~~~~~~~

[Game Name] is the name of your game

## Main.cpp
Now it's time to start programming your game.
First create Main.cpp.

### Including Headers
~~~{.c}
#include "MyActor.h"

#include <Core/Entry.h>

#include <Level.h>
#include <Actor.h>

#include <Components/CameraComponent.h>
#include <Components/ModelComponent.h>
#include <Components/CollisionComponent.h>

#include <Core/Media/InputMedia.h>
#include <Core/Media/WindowMedia.h>
#include <Core/Media/GraphicsMedia.h>

#include <Core/Media/Graphics/Texture.h>
#include <Core/Media/Graphics/GraphicsBuffer.h>

#include <Core/Media/InputCodes.h>

#include <Core/MediaDevices/InputDevice.h>
~~~

#### Windows
~~~{.c}
#include <Core/MediaBackends/DirectX/D3D/D3DRenderer.h>
#include <Core/MediaBackends/DirectX/DXWindow.h>
#include <Core/MediaBackends/XInput/XInput.h>
~~~

#### MacOS/Linux
~~~{.c}
#include <Core/MediaBackends/OpenGL/OGLRenderer.h>
#include <Core/MediaBackends/SDL/SDLWindow.h>
#include <Core/MediaBackends/SDL/SDLInput.h>
~~~

### Creating Media Objects

#### Windows
~~~{.c}
Unique<MWindow> window = CreateUnique<DXWindow>(500, 500, "Name Of Your Game");
Unique<MRenderer> renderer = CreateUnique<D3DRenderer>(*window);
Unique<MInput> input = CreateUnique<XInput>();
~~~

#### MacOS/Linux
~~~{.c}
Unique<MWindow> window = CreateUnique<SDLWindow>(500, 500, "Name Of Your Game");
Unique<MRenderer> renderer = CreateUnique<OGLRenderer>(*window);
Unique<MInput> input = CreateUnique<SDLInput>();
~~~

### Loading Texture File
Create a bitmap file with a width of 1024 and a height of 512. Draw your first texture on the left side, and the other texture on the right side. Make sure you save it as 32 bit color.

~~~~~~{.c}
std::vector<Shared<ModelTexture>> textures = LoadTextureFile("path/to/image.bmp", 512);
~~~~~~

### Creating The Level
~~~~{.c}
Level lvl = Level();

lvl.gravity = -0.05f;
lvl.model_textures = textures;
~~~~

### Creating The Components
~~~{.c}
Shared<CModel> box = lvl.CreateComponent<CModel>( Cube(
    5.0f,
    std::vector{textures[0]}, std::vector{textures[0]},
    std::vector{textures[0]}, std::vector{textures[0]},
    std::vector{textures[1]}, std::vector{textures[0]},
));

Shared<CModel> grass = lvl.CreateComponent<CModel>( Cube(
    100.0f, 1.0f, 100.0f
    std::vector{textures[0]}, std::vector{textures[0]},
    std::vector{textures[0]}, std::vector{textures[0]},
    std::vector{textures[1]}, std::vector{textures[0]},
));
~~~

### Setting Up The Actors
~~~~~~~~~~~~~~~~~~~~~~{.c}
Shared<MyActor> actor = CreateShared<MyActor>();
actor->AddComponent<CCamera>(camera);
actor->AddComponent<CModel>(box);
actor->AddComponent<CCollision>(collision);

Shared<Actor> terrain = CreateShared<Actor>();
terrain->AddComponent<CModel>(grass);
terrain->enable_tick = false;

lvl.AddActor(strevo);
lvl.AddActor(terrain);
~~~~~~~~~~~~~~~~~~~~~~

Yes, even the ground itself is an Actor

### Camera
The camera can be adjusted by changing the throttle variables. Use AttachRod() to attach the camera to the actor.

~~~{.c}
camera->rod_yaw_throttle = -90.0f;
camera->rod_pitch_throttle = 90.0f;
camera->fov = 70.0f;

camera->AttachRod(actor, 10.0f, Vector3(0, 0, 0), true);
~~~

### Input Binding

For this tutorial, we'll use the keyboard and mouse device. If you want to use game controllers, make sure the device isn't NULL before binding any buttons or analogs.

~~~~~~~~~~~~~~~~~~~~{.c}
Shared<InputDevice> keyboard = input->GetInputDevice(KEYBOARD_DEVICE);

keyboard->BindButton(KEY_W, actor, &MyActor::OnKeyForward);
keyboard->BindButton(KEY_S, actor, &MyActor::OnKeyBack);
keyboard->BindButton(KEY_A, actor, &MyActor::OnKeyLeft);
keyboard->BindButton(KEY_D, actor, &MyActor::OnKeyRight);

Shared<InputDevice> mouse = input->GetInputDevice(MOUSE_DEVICE);

mouse->BindAnalog(MOUSE_X, camera, &CCamera::RodYaw);
mouse->BindAnalog(MOUSE_Y, camera, &CCamera::RodPitch);
~~~~~~~~~~~~~~~~~~~~

### Starting The Game
Once this function starts, there is no going back.
~~~{.c}
Start(std::move(window), std::move(renderer), std::move(input), lvl);
~~~

## MyActor
Create two files, MyActor.h and MyActor.cpp. You can change the name to whatever you want.

### MyActor.h
~~~~~{.c}
#ifndef MYACTOR_H
#define MYACTOR_H

#include <Actor.h>
#include <Components/CameraComponent.h>
#include <Events/InputEvents.h>

class MyActor : public Actor
{
public:
    MyActor();

    void Tick();

    void OnKeyForward(EButtonInput* e);
    void OnKeyBack(EButtonInput* e);
    void OnKeyLeft(EButtonInput* e);
    void OnKeyRight(EButtonInput* e);

    void JumpBegin(EButtonInput* e);
    void JumpEnd(EButtonInput* e);

private:
    Vector3 relative_velocity;
};

#endif
~~~~~

### MyActor.cpp
~~~~~~~~~~~{.c}
#include "Strevo.h"
#include <Core/Time.h>
#include <Common/Mathematics.h>

MyActor::MyActor() : Actor()
{
    relative_velocity = Vector3(0, 0, 0);
}

void MyActor::Tick()
{
    float direct = relative_velocity.direct;
    float side = relative_velocity.side;


    Shared<CCamera> camera = GetComponent<CCamera>();

    if(camera)
    {
        float yaw = DegreesToRadians(camera->rotation.yaw);
        float sin_yaw = sin(yaw);
        float cos_yaw = cos(yaw);

        position_velocity.x = sin_yaw * direct + -cos_yaw * side;
        position_velocity.z = cos_yaw * direct + sin_yaw * side;

        rotation_velocity.yaw = camera->rod_rotation_velocity.yaw * Delay();
    }

    Actor::Tick();
}

void MyActor::OnKeyForward(EButtonInput* e)
{
    relative_velocity.direct = 10 * e->pressed * Delay();
}

void MyActor::OnKeyBack(EButtonInput* e)
{
    relative_velocity.direct = -10 * e->pressed * Delay();
}

void MyActor::OnKeyLeft(EButtonInput* e)
{
    relative_velocity.side = -10 * e->pressed * Delay();
}

void MyActor::OnKeyRight(EButtonInput* e)
{
    relative_velocity.side = 10 * e->pressed * Delay();
}

void MyActor::JumpBegin(EButtonInput* e)
{
    //Vector3 position_velocity = GetPositionVelocity();
    //position_velocity.y = 0.1f * Delay();
    //SetPositionVelocity(position_velocity);
}

void MyActor::JumpEnd(EButtonInput* e)
{

}
~~~~~~~~~~~
