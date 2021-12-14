#ifndef SYSTEMS_H
#define SYSTEMS_H

struct Actor;
struct CModel;
struct CCamera;
struct Controller;
struct ModelTexture;
struct CCollision;

void VertexSystem(std::vector<Shared<CModel>>& models, std::vector<Shared<ModelTexture>>& textures);
void ActorSystem(std::vector<Shared<Actor>>& actors);
void CollisionSystem(std::vector<Shared<CCollision>> collisions);
void ViewProjectionSystem(std::vector<Shared<CCamera>>& cameras, std::vector<Shared<CModel>>&
    transforms);
void RenderSystem(std::vector<Shared<CModel>>& models);
void InputSystem(std::vector<Shared<Controller>>& controllers);

#endif
