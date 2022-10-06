#ifndef D3DBUFFER_H
#define D3DBUFFER_H

#include "Core/Media/Graphics/GraphicsBuffer.h"

struct D3DBuffer : GraphicsBuffer
{
    D3DBuffer(ComPtr<ID3D11DeviceContext> device_context);

private:
    D3D11_BUFFER_DESC m_buffer_desc;
    D3D11_SUBRESOURCE_DATA m_init_data;
    ComPtr<IDED11Buffer> m_buffer;

    ComPtr<ID3D11DeviceContext> m_device_context;
};

#endif
