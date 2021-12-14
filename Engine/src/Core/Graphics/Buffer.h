#ifndef BUFFER_H
#define BUFFER_H

namespace Graphics
{
    struct Buffer
    {
        Buffer();
        ~Buffer();

        //Copy = Bad
        Buffer(const Buffer&) = delete;
        Buffer &operator=(const Buffer&) = delete;

        //Move = Good
        Buffer(Buffer&& other);
        Buffer& operator=(Buffer&& other);

        uint GetID();
        size_t GetSize();

        virtual void Init();
        virtual void Clear();
        virtual void Bind();
        virtual void AddData(u8* data, uint data_amount, uint data_bytesize) = 0;

    protected:
        virtual void Release();
        uint id;
        size_t size;
    };
}
#endif