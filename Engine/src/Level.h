#ifndef LEVEL_H
#define LEVEL_H


class Actor;
struct CModel;
class Controller;
struct Component;
struct CCamera;
struct ModelTexture;
struct CCollision;

//void AddWidgetToCurrentLevel(Widget widget);

//std::vector<CollisionTri> ReadCollisionFile(std::string file);
//void StartLevel(Level& level);
//void Run();

struct Level
{
    Level(Shared<ModelTexture> sky);
    
    //Level();
    std::vector<Shared<Controller>> controllers;
    std::vector<Shared<Actor>> actors;

    template<class C, typename... Args> Shared<C> CreateComponent(Args&&... args);

    std::vector<Shared<ModelTexture>> model_textures;

    //Components
    std::vector<Shared<CModel>> model_components;
    std::vector<Shared<CCamera>> camera_components;
    std::vector<Shared<CCollision>> collision_components;
    /*std::vector<Shared<CollisionComponent>> model_components;*/

    void AddActor(Shared<Actor> actor);
    void Init();

    //std::function<void()> script;
    //std::vector<CollisionTri> flat_collisions;
    //std::vector<Widget> widgets;

    //float gravity;
};

template<class C, typename... Args> Shared<C> Level::CreateComponent(Args&&... args)
{
    Shared<C> component = CreateShared<C>(std::forward<Args>(args)...);
    component->AttachToLevel(*this);
    return component;
}

#endif
