#include "Actor.h"
#include "Core/Clock.h"
#include "Common/Hex.h"
#include "Common/Log.h"
#include "Level.h"

Actor::Actor() : Object()
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
}

Actor::Actor(Vector3 position, Vector3 rotation, Vector3 scale) : Object(position, rotation, scale)
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
}

Actor::Actor(Shared<Model> model) : Object(model)
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
}

Actor::Actor(Shared<Model> model, Vector3 position, Vector3 rotation, Vector3 scale) : 
    Object(model, position, rotation, scale)
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
}

Actor::~Actor()
{
    delete collision;
    delete current_level;
}

void Actor::Tick()
{
    if(can_fall && current_level)
        ChangePositionVelocity(0, (Delay() > 1) ? current_level->gravity : current_level->gravity * Delay(), 0);

    ChangePosition(GetPositionVelocity());
    ChangeRotation(GetRotationVelocity());
    ChangeScale(GetScaleVelocity());

    for(Shared<Component> component : components)
    {
        component->SetPosition(GetPosition() + component->GetRelativePosition());
        component->SetRotation(GetRotation() + component->GetRelativeRotation());
        component->SetScale(GetScale() + component->GetRelativeScale());
    }
}  

void Actor::CreateHitBox(float depth, float height, float width)
{
    collision = new CollisionBox(GetPosition(), depth, height, width);
}

void Actor::AddComponent(Shared<Component> component)
{
    components.push_back(component);
}