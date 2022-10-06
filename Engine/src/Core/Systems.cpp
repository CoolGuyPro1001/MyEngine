#include "Systems.h"
#include "Actor.h"

#include "Components/ModelComponent.h"
#include "Components/CameraComponent.h"
#include "Components/CollisionComponent.h"

#include "Common/Vertex.h"

#include "Media/InputMedia.h"
#include "Media/WindowMedia.h"
#include "Media/GraphicsMedia.h"
#include "Media/Graphics/Texture.h"
#include "Media/Graphics/GraphicsBuffer.h"

//Call This Function BEFORE The Game Loop
void VertexSystem(MRenderer& renderer, std::vector<Shared<CModel>>& models, std::vector<Shared<ModelTexture>>& textures)
{
    uint texture_size;
    if(textures.size() > 0)
        texture_size = textures[0]->size;

    renderer.TextureManager->InitModelTextureArray(textures, texture_size);

    std::vector<Vertex> vertex_data;
    std::vector<u8>& mvp_data = renderer.ub_mvp->Data();
    mvp_data = std::vector<u8>(16 * sizeof(float));

    for(Shared<CModel> m : models)
    {
        vertex_data.insert(vertex_data.end(), m->vertices.begin(), m->vertices.end());
        m->buffer_size = m->vertices.size() * sizeof(Vertex);

        uint total_actor_mvp_bytesize = m->actors.size() * 16 * sizeof(float);
        mvp_data.resize(mvp_data.size() + total_actor_mvp_bytesize);
    }

    renderer.vb_instance->Fill((u8*) &vertex_data[0], vertex_data.size() * sizeof(Vertex));
}

void ActorSystem(std::vector<Shared<Actor>>& actors)
{
    for(Shared<Actor>& actor : actors)
    {
        if(actor->enable_tick)
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
void ViewProjectionSystem(MRenderer& renderer, MWindow& window, std::vector<Shared<CCamera>>& cameras, std::vector<Shared<CModel>>& models)
{
    Shared<GraphicsBuffer> mvp_buffer = renderer.ub_mvp;
    Shared<GraphicsMath> graphics_math = renderer.Math;
    std::vector<u8>& mvp_data = mvp_buffer->Data();

    for(const Shared<CCamera>& camera : cameras)
        camera->Tick();

    //For now have cameras[0] be default
    Shared<CCamera> world_camera = cameras[0];

    Mat4 view = graphics_math->GenerateViewMatrix(world_camera->position, world_camera->looking_at, world_camera->up);
    Mat4 projection = graphics_math->GeneratePerspectiveMatrix(world_camera->fov, window.Width(), window.Height());

    uint index = 0;

    //Ignore The Last Model, For That Is The Skybox
    for(int i = 0; i < models.size() - 1; i++)
    {
        for(Shared<Actor> a : models[i]->actors)
        {
            Mat4 model_matrix = graphics_math->GenerateModelMatrix(a->position, a->rotation, a->scale);
            Mat4 mvp = graphics_math->GenerateMVP(model_matrix, view, projection);

            memcpy(&mvp_data[index], mvp.data, 16 * sizeof(float));
            index += 16 * sizeof(float);
        }
    }

    //Only have the rotation part of view matrix be in mvp for sky box
    //This is done by taking the top left glm::mat3(view) then setting it to a glm::mat4
    //IdentityMatrix() Represents A 1x1x1 Cube
    Mat3 view_rotation(view);
    Mat4 skybox_view(view_rotation);
    Mat4 skybox_mvp = graphics_math->GenerateMVP(graphics_math->IdentityMatrix(), skybox_view, projection);
    graphics_math->MVPToSkyBoxMVP(skybox_mvp);

    //Put MVP Of Skybox Last
    memcpy(&mvp_data[index], skybox_mvp.data, 16 * sizeof(float));

    //Send MVP Data To Renderer's Uniform Buffer Manager
    //all_mvp_data.push_back(Renderer::IdentityMatrix());

    size_t all_mvp_bytesize = mvp_data.size();
    mvp_buffer->Remove(0, all_mvp_bytesize);
    mvp_buffer->Mirror();
}

void RenderSystem(MRenderer& renderer, std::vector<Shared<CModel>>& models)
{
    uint buffer_offset = 0;
    uint mvp_index = 0;

    renderer.ClearDrawBuffers();

    if(!renderer.PrepareDraw())
        return;

    for(int i = 0; i < models.size() - 1; i++)
    {
        Shared<CModel> m = models[i];
        renderer.Draw(m->buffer_size, m->actors.size(), buffer_offset, mvp_index); //Draw All Actor Instances Of Model [m]
        mvp_index += m->actors.size();
        buffer_offset += m->buffer_size;
    }

    //Shared<Actor> skybox = models[models.size() - 1]->actors[0];
    renderer.DrawSkyBox(buffer_offset, mvp_index);
}

void EventSystem(MWindow& window, MInput& input)
{
    window.ProcessEvents();
    input.CollectEvents();
    input.HandleEvents();
}
