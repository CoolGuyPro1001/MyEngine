#include "IndexBuffer.h"
#include "GLDebug.h"

/*namespace Graphics
{
    ///@brief Default Constuctor. The data points to null
    IndexBuffer::IndexBuffer() : data(nullptr)
    {
        glCreateBuffers(1, &name));
    }

    ///@brief Constructor For Setting Data
    ///@param data The data for the IndexBuffer
    IndexBuffer::IndexBuffer(std::shared_ptr<std::vector<unsigned short>> data) : data(data)
    {
        glCreateBuffers(1, &name));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, name));

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.get()->size() * sizeof(unsigned short), &(*data.get())[0], GL_STATIC_DRAW));
    }

    ///@brief Gets The Size of Data In Bytes
    ///@return The Size Of The IndexBuffer's Data In Bytes
    int IndexBuffer::ByteSize()
    {
        return (data != nullptr) ? data.get()->size() * sizeof(unsigned short) : 0;
    }

    ///@brief Gets The IndexBuffer's Data To Be Modified
    ///@param proof_of_access Pointer To IndexBuffer
    ///@return Data Of IndexBuffer If proof_of_access Is Same as this
    std::vector<unsigned short>* IndexBuffer::GetData(IndexBuffer* proof_of_access)
    {
        if(proof_of_access != this)
        {
            return nullptr;
        }

        return data.get();
    }

    ///@brief Binds IndexBuffer To GL_ELEMENT_ARRAY_BUFFER
    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, name));
    }

    ///@brief Unbinds IndexBuffer From GL_ELEMENT_ARRAY_BUFFER
    void IndexBuffer::UnBind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    ///@brief Updates The Data That May Have Changed From Outside Functions
    void IndexBuffer::RefreshData()
    {
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.get()->size() * sizeof(unsigned short), &(*data.get())[0], GL_STATIC_DRAW));
        UnBind();
    }
}*/