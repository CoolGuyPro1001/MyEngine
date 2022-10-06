#ifndef SYSTEMS_H
#define SYSTEMS_H

struct Actor;
struct CModel;
struct CCamera;
struct ModelTexture;
struct CCollision;
class MInput;
class MWindow;
class MRenderer;

//Called Only Onced Per Level, Sets The 3D Model Buffer To Model Components
void VertexSystem(MRenderer& renderer, std::vector<Shared<CModel>>& models, std::vector<Shared<ModelTexture>>& textures);

//Updates Actors
void ActorSystem(std::vector<Shared<Actor>>& actors);

//Detecting And Handling Collision
void CollisionSystem(std::vector<Shared<CCollision>> collisions);

//Sets The ModelViewProjection Buffer, Which Is Used For 3D Rendering
void ViewProjectionSystem(MRenderer& renderer, MWindow& window, std::vector<Shared<CCamera>>& cameras, std::vector<Shared<CModel>>&
    transforms);

//Renders 3D And 2D Graphics (Like Text)
void RenderSystem(MRenderer& renderer, std::vector<Shared<CModel>>& models);

//Handles Events
void EventSystem(MWindow& window, MInput& input);


#endif
