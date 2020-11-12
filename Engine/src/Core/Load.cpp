#include "Load.h"

namespace Engine
{
    void LoadLevel(Level& level)
    {
        //Delete Graphics Buffer
        Graphics::DeleteBuffer(*Graphics::BufferId());
        
        //Init A New Buffer
        Graphics::InitVertexBuffer(*Graphics::BufferId());

        //A vector of pointers to models (pointer to a vector of Vertices objects)
        std::vector<Shared<Model>> model_ptrs;
        uint off_set_pointer = 0;
        bool model_exists = false;

        for(int i = 0; i < level.actors.size(); i++)
        {
            int i1 = 0;
            while(i1 < model_ptrs.size())
            {
                if(&(level.actors[i].model) == &(model_ptrs[i1]))
                {
                    model_exists = true;

                    //Increase render count for that model
                    Graphics::RenderCounts()[i1]++;
                }

                i1++;
            }

            if(model_exists)
            {
                model_exists = false;
                break;
            }

            model_ptrs.push_back(level.actors[i].model);

            Shared<Model> m = model_ptrs[i1];
            m->off_set = off_set_pointer;
            
            Graphics::AddDataToBuffer(m->vertices, *Graphics::VaoId());
            Graphics::FormatData(*Graphics::VaoId(), off_set_pointer);

            Graphics::RenderCounts().push_back(1);
            Graphics::AddModelMatrix(&level.actors[i].position, &level.actors[i].rotation, &level.actors[i].scale);
            
            off_set_pointer += m->vertices.size() * sizeof(Vertex);
            Graphics::ObjectSizes().push_back(off_set_pointer);
        }
    }
}