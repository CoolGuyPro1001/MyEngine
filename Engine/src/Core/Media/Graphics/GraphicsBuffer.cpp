#include "GraphicsBuffer.h"

MemorySection::MemorySection(size_t offset, size_t size)
{
    this->offset = offset;
    this->size = size;
}

GraphicsBuffer::GraphicsBuffer(bool mirror_data) : m_mirror_data(mirror_data)
{
    m_size = 0;
    if(mirror_data)
        m_data = std::vector<u8>();
}

size_t GraphicsBuffer::GetSize()
{
    return m_size;
}

std::vector<u8>& GraphicsBuffer::Data()
{
    return m_data;
}

void GraphicsBuffer::Remove(size_t offset, size_t size)
{
    auto lower_cmp = [](MemorySection ms, size_t offset)
    {
        return ms.offset < offset;
    };

    //Find The First Free Memory Block
    auto ms = std::lower_bound(m_free_memory.begin(), m_free_memory.end(), offset, lower_cmp);

    if(ms == m_free_memory.end())
    {
        if(offset + size >= m_size)
            size = m_size - offset;

        m_free_memory.emplace_back(offset, size);
        return;
    }

    //Check If The Free Memory Block Is Extendable
    if(ms->offset + ms->size == offset)
    {
        ms->size += size; //Extend Right

        //If The Extended Free Memory Block Reaches The Next Memory Block, Combine Them
        if(ms->offset + ms->size == (ms + 1)->offset)
            CombineFreeMemory(ms);

        if(offset + size == m_size)
            ms->size = m_size - offset;
        return;
    }

    //Go For The Next Free Memory Block
    if(offset + size == (++ms)->offset)
    {
        //Extend Left
        ms->offset = offset;
        ms->size += size;

        if(offset + size == m_size)
            ms->size = m_size - offset;
        return;
    }
}

void GraphicsBuffer::Mirror()
{
    Insert(&m_data[0], m_data.size());
}

void GraphicsBuffer::CombineFreeMemory(auto ms)
{
    ms->size += (ms + 1)->size;
    m_free_memory.erase(ms);
}
