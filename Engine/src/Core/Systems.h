#ifndef SYSTEMS_H
#define SYSTEMS_H

struct Vector3;
struct Color;
struct Actor;
struct CModel;
struct CCamera;
struct ModelTexture;
struct CCollision;
class MInput;
class MWindow;
class MRenderer;

//Called Only Onced Per Level, Sets The 3D Model Buffer To Model Components
void VertexSystem(MRenderer* renderer, std::vector<Shared<CModel>>& models, std::vector<Shared<ModelTexture>>& textures);

//Updates Actors
void ActorSystem(std::vector<Shared<Actor>>& actors);

//Detecting And Handling Collision
void CollisionSystem(std::vector<Shared<CCollision>> collisions);

//Sets The Model Buffer
void ModelSystem(MRenderer* renderer, std::vector<Shared<CModel>>& models);

//Lighting
void LightingSystem(MRenderer* renderer, Shared<CCamera> camera, float ambient_factor, float specular_factor, Vector3 light_source_position, Color light_color);

//Sets The ModelViewProjection Buffer, Which Is Used For 3D Rendering
void ViewProjectionSystem(MRenderer* renderer, MWindow* window, std::vector<Shared<CCamera>>& cameras);

//Renders 3D And 2D Graphics (Like Text)
void RenderSystem(MRenderer* renderer, std::vector<Shared<CModel>>& models);

//Handles Events
void EventSystem(MWindow* window, MInput* input);


#endif
