#include "Load.h"

namespace Engine
{
    void LoadLevel(Level& level, uint& buffer_id)
    {
        //Delete Graphics Buffer
        Graphics::DeleteBuffer(buffer_id);
        
        //Init A New Buffer
        Graphics::InitVertexBuffer(buffer_id);

        //A vector of pointers to models (pointer to a vector of Vertices objects)
        std::vector<Model*> model_ptrs;
        std::vector<uint> off_sets;
        uint off_set_pointer = 0;

        for(int i = 0; i < level.actors.size(); i++)
        {
            for(int i1 = 0; i1 < model_ptrs.size(); i1++)
            {
                if(&(level.actors[i].model) != &(model_ptrs[i1]))
                {
                    model_ptrs[i1] = level.actors[i].model;
                }
                else
                {
                    Graphics::AddDataToBuffer(model_ptrs[i1]->vertices, model_ptrs[i1]->id);
                    off_sets.push_back(off_set_pointer);
                    Graphics::FormatData(model_ptrs[i1]->id, off_sets[i1]);
                }
            }
        }
    }
}