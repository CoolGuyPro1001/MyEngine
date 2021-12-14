#include "Systems.h"

#include "Components/ModelComponent.h"
#include "Components/CameraComponent.h"
#include "Components/CollisionComponent.h"
#include "Actor.h"

#include "Graphics/Graphics.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/UniformBuffer.h"
#include "Graphics/Texture.h"

#include "Common/Vertex.h"
#include "Events.h"

//Call This Function BEFORE The Game Loop
void VertexSystem(std::vector<Shared<CModel>>& models, std::vector<Shared<ModelTexture>>& textures)
{
    uint texture_size;
    if(textures.size() > 0)
        texture_size = textures[0]->size;

    Texture::InitModelTextureArray(textures, texture_size);
    Graphics::ClearUniformBuffers();

    for(Shared<CModel> m : models)
    {
        Graphics::buffer3d.AddData((u8*) &(m->vertices[0]), m->vertices.size(), sizeof(Vertex));
        m->buffer_size = m->vertices.size() * sizeof(Vertex);
    }

    Graphics::FormatVertexBuffers();
}

void ActorSystem(std::vector<Shared<Actor>>& actors)
{
    for(Shared<Actor>& actor : actors)
    {
        actor->Tick();
    }
}

void CollisionSystem(std::vector<Shared<CCollision>> collisions)
{
    for(Shared<CCollision>& c: collisions)
    {
        Vector3& velocity = c->actors[0]->position_velocity;

        if(velocity == Vector3(0, 0, 0))
            continue;

        Vector3& position = c->actors[0]->position;
        Vector3 position_before = position - velocity;

        float half_depth = c->depth / 2;
        float half_height = c->height / 2;
        float half_width = c->width / 2;

        //Four Corners
        Vector3 current_a = position + Vector3(half_depth, half_height, half_width);
        Vector3 current_b = position - Vector3(half_depth, half_height, half_width);

        //Detect CCollision With Other Actors
        for(Shared<CCollision>& other : collisions)
        {
            if(other == c)
                continue;

            float other_half_depth = other->depth / 2;
            float other_half_height = other->height / 2;
            float other_half_width = other->width / 2;
            Vector3 other_position = other->actors[0]->position;

            Vector3 other_a = other_position + Vector3(other_half_depth, other_half_height, other_half_width);
            Vector3 other_b = other_position - Vector3(other_half_depth, other_half_height, other_half_width);

            if(current_a >= other_b && current_b <= other_a)
            {
                position = position_before;
                velocity = Vector3(0, 0, 0);
            }
        }
    }
}

//For Cameras and MVPs
void ViewProjectionSystem(std::vector<Shared<CCamera>>& cameras, std::vector<Shared<CModel>>& models)
{
    std::vector<glm::mat4> object_mvps;

    for(const Shared<CCamera>& camera : cameras)
        camera->Tick();

    //For now have cameras[0] be default
    Shared<CCamera> world_camera = cameras[0];

    glm::mat4 view = Graphics::GenerateViewMatrix(world_camera->position, world_camera->looking_at, world_camera->up);
    glm::mat4 projection = Graphics::GeneratePerspectiveMatrix(world_camera->fov);

    //Only have the rotation part of view matrix be in mvp for sky box
    //This is done by taking the top left glm::mat3(view) then setting it to a glm::mat4

    //Put MVP Of Sky Box Inside Model_matrix of actor of sky box
    models[models.size() - 1]->actors[0]->model_matrix = projection * glm::mat4(glm::mat3(view));

    for(int i = 0; i < models.size() - 1; i++)
    {
        for(Shared<Actor> a : models[i]->actors)
        {
            object_mvps.push_back(projection * view * a->model_matrix);
        }
    }

    object_mvps.push_back(Graphics::GetIdentityMatrix());
    Graphics::mvp_buffer.AddData((u8*) &object_mvps[0], object_mvps.size(), sizeof(glm::mat4));
}

void RenderSystem(std::vector<Shared<CModel>>& models)
{
    uint buffer_offset = 0;
    uint mvp_index = 0;

    Graphics::ClearDrawBuffers();

    if(!Graphics::PrepareDraw())
        return;

    for(int i = 0; i < models.size() - 1; i++)
    {
        Shared<CModel> m = models[i];
        Graphics::Draw(m->buffer_size, m->actors.size(), buffer_offset, mvp_index);
        mvp_index += m->actors.size();
        buffer_offset += m->buffer_size;
    }

    Graphics::DrawSkyBox(buffer_offset, models[models.size() - 1]->actors[0]->model_matrix);
    Graphics::UpdateGraphics();
}

void InputSystem(std::vector<Shared<Controller>>& controllers)
{
    PollEvents(controllers);
}
