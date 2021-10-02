#ifndef LEVEL_H
#define LEVEL_H

#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Controller.h"
#include "GUI/Widget.h"

class Model;
class Actor;

void AddTextureToCurrentLevel(Shared<Texture> texture);
void AddModelToCurrentLevel(Shared<Model> model);
void AddActorToCurrentLevel(Shared<Actor> actor);
void AddCameraToCurrentLevel(Shared<Camera> camera);
void AddControllerToCurrentLevel(Shared<Controller> controller);
void AddWidgetToCurrentLevel(Widget widget);

std::vector<CollisionTri> ReadCollisionFile(std::string file);
void StartLevel(Level& level);
void Run();

struct Level
{
    Level();
    
    std::vector<Shared<Texture>> textures;
    std::vector<Shared<Model>> models;
    std::vector<Shared<Actor>> actors;
    std::vector<Shared<Component>> components;
    std::vector<Shared<Camera>> cameras;
    std::vector<Shared<Controller>> controllers;

    std::function<void()> script;

    Shared<Object> sky_block;
    Shared<Object> terrain;
    std::vector<CollisionTri> flat_collisions;

    std::vector<Widget> widgets;

    float gravity;
};
#endif