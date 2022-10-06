#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H

//Represents A Part Of Memory
//Used For VRAM, Might Use For RAM In The Future
struct MemorySection
{
    MemorySection(size_t offset, size_t size);
    size_t offset;
    size_t size;
};

struct GraphicsBuffer
{
    GraphicsBuffer(bool mirror_data);

    size_t GetSize();
    void Mirror(); //Copies Data From RAM To VRAM
    void Remove(size_t offset, size_t size);
    std::vector<u8>& Data();

    virtual void Init(size_t size = 0) = 0;
    virtual void Destroy() = 0;
    virtual void Fill(u8* data, size_t size) = 0; //The size is in bytes
    virtual void Insert(u8* data, size_t size) = 0;

protected:
    size_t m_size;
    bool m_mirror_data; //If True, Data From VRAM Will Be Mirrored To RAM
    std::vector<u8> m_data;
    std::vector<MemorySection> m_free_memory;

private:
    void CombineFreeMemory(auto ms);
};
#endif
