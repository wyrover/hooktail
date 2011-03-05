#pragma once

#include "htAppAPI.h"

#include <d3dx10.h>
#include <string>


namespace hooktail
{

class AppD3D10 : public AppAPI
{
public:
                                AppD3D10();

    // Windows COM
    LRESULT                     MsgProc(UINT in_msg, WPARAM in_wParam, LPARAM in_lParam);

    virtual VOID                InitApp();


protected:
    virtual HRESULT             Update();
    virtual VOID                Render();
    virtual HRESULT             OnResize();

private:
    HRESULT                     InitAPI();

    std::wstring                m_frameStats;

    ID3D10Device*               m_pD3dDevice;
    IDXGISwapChain*             m_pSwapChain;
    DXGI_SAMPLE_DESC            m_msaaDesc;

    ID3D10RenderTargetView*     m_pBackBufferView;
    DXGI_FORMAT                 m_backBufferFormat;
    
    ID3D10Texture2D*            m_pDSBuffer;
    ID3D10DepthStencilView*     m_pDSView;
    DXGI_FORMAT                 m_dsFormat;

    ID3DX10Font*                m_pFont;

    D3D10_DRIVER_TYPE           m_d3dDriverType;

    D3DXCOLOR                   m_clearColor;

    BOOL                        m_isWindowed;
};

inline
AppD3D10::AppD3D10()
    : AppAPI(HT_API_DX)
    , m_frameStats(L"")
    , m_pD3dDevice(0)
    , m_pSwapChain(0)
    , m_pBackBufferView(0)
    , m_backBufferFormat(DXGI_FORMAT_R8G8B8A8_UNORM)
    , m_pDSBuffer(0)
    , m_pDSView(0)
    , m_dsFormat(DXGI_FORMAT_D24_UNORM_S8_UINT)
    , m_pFont(0)
    , m_d3dDriverType(D3D10_DRIVER_TYPE_HARDWARE)
    , m_clearColor(D3DXCOLOR(0.1f, 0.33f, 0.7f, 1.0f))
    , m_isWindowed(true)
{
    HT_TRACE_IN();

    m_msaaDesc.Count            = 1;
    m_msaaDesc.Quality          = 0;

    InitAPI();

    HT_TRACE_OUT();
}

} // namespace hooktail
