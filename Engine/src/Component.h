#ifndef COMPONENT_H
#define COMPONENT_H

struct Level;
struct Actor;

/*
 * Create Components Using CreateComponent() From A Level Object
 * Do Not Call AttachToLevel, CreateComponent() Already Calls It
 * Add Component To An Actor By Using AddComponent() From The Actor Object
 * Components Are Used By Systems
 * Ex: ViewProjectionSystem() Uses CCamera And CModel
 */

struct Component
{
    virtual void AttachToLevel(Level& lvl) = 0;
    std::vector<Shared<Actor>> actors;
};

#endif
