#include "D3DGraphics.h"

//For Now, Create Device Under Single Thread
D3DRenderer::D3DRenderer(HWND window_handle, bool debug)
{
    //Create Device And Swapchain
    UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
    D3D_FEATURE_LEVEL features[2]
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1,
    };

    DXGI_SWAP_CHAIN_DESC swap_desc;
    swap_desc.BufferDesc = IDXGIOutput::GetDisplayModeList();
    swap_desc.SampleDesc.Count = 1;
    swap_desc.BufferUsage = DXGI_USAGE_RENER_TARGET_OUTPUT;
    swap_desc.BufferCount = 2;
    swap_desc.OutputWindow = window_handle;
    swap_desc.Windowed = true;
    swap_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    swap_desc.Flags =
        DXGI_SWAP_CHAIN_FLAG_NONPREROTADED |
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH |
        DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY |
        DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO |
        DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED |
        DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

    if(debug)
        flags |= (D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_DEBUGGABLE);

    D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        flags,
        features,
        2,
        D3D11_SDK_VERSION,
        &swap_desc,
        &m_swap_chain,
        &m_device,
        nullptr,
        &m_device_context
    );

    /*D3D11_INPUT_ELEMENT_DESC input_desc[2] =
    {

    //Create Input Layout
    device->CreateInputLayout
    (*/

    m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), &m_back_buffer);

    m_device->CreateRenderTargetView(m_back_buffer.Get(), nullptr, &m_render_target);

    Math = CreateShared<D3DMath>();
    vb_instance = CreateShared<D3DBuffer>(m_device_context);
}

D3DRenderer::PrepareDraw()
{
    m_device_context->OMSetRenderTargets(1, render_target.GetAddressOf(), nullptr);

    float color[4] = {0, 0, 0, 1};
    m_device_context->ClearRenderTargetView(render_target.Get(), color);

    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    m_device_context->IASetVertexBuffers(0, 1, vertexbuffer.GetAddressOf(), &stride, &offset);

    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

D3DRenderer::Draw()
{
    m_device_context->OMSetRenderTargets(1, m_render_target.GetAddressOf(), nullptr);

    float color[4] = {0, 0, 0, 1};
    m_device_context->ClearRenderTargetView(m_render_target.Get(), color);
}

D3DRenderer::SwapBuffers()
{
    m_swap_chain->Present(1, 0);
}
