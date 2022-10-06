#include "D3DVBManager.h"
#include "Common/Vertex.h"

D3DVertexBuffer::D3DVertexBuffer()
{

}

D3DVertexBuffer::~D3DVertexBuffer()
{
    //Release();
}

void D3DVertexBuffer::InitBuffer()
{
    m_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
    m_buffer_desc.ByteWidth = sizeof(VertexFormat) * vertex_amount;
    m_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    m_buffer_desc.CPUAccessFlags = 0;
    m_buffer_desc.MiscFlags = 0;

    m_init_data = {0};
    //init_data.pSysMem = verticesCombo;
    m_init_data.SysMemPitch = 0;
    m_init_data.SysMemSlicePitch = 0;

    g_pd3dDevice->CreateBuffer(&m_buffer_desc, &m_init_data,
        &m_buffer);
}
