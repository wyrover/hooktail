#pragma once

#include "htAppWindows.h"

#include <d3dx10.h>
#include <string>


namespace hooktail {

class htAppD3D10 : public htAppWindows
{
public:
                                htAppD3D10();

    virtual LRESULT             MsgProc(UINT in_msg, WPARAM in_wParam, LPARAM in_lParam);

protected:

    HRESULT                     InitAPI();


private:


    std::wstring                m_frameStats;

    ID3D10Device*               m_pD3dDevice;
    IDXGISwapChain*             m_pSwapChain;
    ID3D10Texture2D*            m_pTex2D;
    ID3D10RenderTargetView*     m_pRTView;
    ID3D10DepthStencilView*     m_pDSView;
    ID3DX10Font*                m_pFont;

    D3D10_DRIVER_TYPE           m_d3dDriverType;

    D3DXCOLOR                   m_clearColor;

    BOOL                        m_isWindowed;
};

inline
htAppD3D10::htAppD3D10()
    : htAppWindows()
    , m_frameStats(L"")
    , m_pD3dDevice(0)
    , m_pSwapChain(0)
    , m_pTex2D(0)
    , m_pRTView(0)
    , m_pDSView(0)
    , m_pFont(0)
    , m_d3dDriverType(D3D10_DRIVER_TYPE_HARDWARE)
    , m_clearColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))
    , m_isWindowed(true)
{
}

} // namespace hooktail
