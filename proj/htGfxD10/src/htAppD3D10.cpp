#include "htAppD3D10.h"

using namespace hooktail;

HRESULT
htAppD3D10::InitAPI()
{
    HRESULT hr = S_OK;

    UINT width  = 0;
    UINT height = 0;

    if(m_isWindowed)
    {
        RECT rc;
        GetClientRect(GetMainWindow(), &rc);
        width  = rc.right - rc.left;
        height = rc.bottom - rc.top;
    }

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd,sizeof(sd));

    sd.BufferDesc.Width         = width;
    sd.BufferDesc.Height        = height;
    sd.BufferDesc.Format        = m_rtFormat;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling       = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferUsage              = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount              = 1;
    sd.OutputWindow             = GetMainWindow();
    sd.Windowed                 = m_isWindowed;
    sd.SwapEffect               = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags                    = 0;
    sd.SampleDesc.Count         = 1;
    sd.SampleDesc.Quality       = 0;

    UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    // Create Device
    hr = D3D10CreateDeviceAndSwapChain(
            NULL,                 //default adapter
            m_d3dDriverType,
            NULL,                 // no software device
            createDeviceFlags, 
            D3D10_SDK_VERSION,
            &sd,
            &m_pSwapChain,
            &m_pD3dDevice);


    // Create Pixel Rendertarget View
//     D3D10_RENDER_TARGET_VIEW_DESC   rtvd = {0};
//     
//     rtvd.Format     = m_rtFormat;
//     rtvd.
    if(hr)
    {

    }




    // Create Depth-Stencil Rendertarget View

    // Set Rendertargets

    // Setup Rasterizer State

    // Setup Depth-Stencil State


   

    // Create Viewport
    D3D10_VIEWPORT vp;
    vp.Width        = width;
    vp.Height       = height;
    vp.MinDepth     = 0.0f;
    vp.MaxDepth     = 1.0f;
    vp.TopLeftX     = 0;
    vp.TopLeftY     = 0;
    m_pD3dDevice->RSSetViewports(1, &vp);

    return hr;
}

LRESULT
htAppD3D10::MsgProc(UINT in_msg, WPARAM in_wParam, LPARAM in_lParam)
{
    htAppWindows::MsgProc(in_msg, in_wParam, in_lParam);

    switch(in_msg)
    {
    case WM_SIZE:
		// Save the new client area dimensions.
		m_clientWidth  = LOWORD(in_lParam);
		m_clientHeight = HIWORD(in_lParam);

        if( m_pD3dDevice )
		{
			if( in_wParam == SIZE_MINIMIZED )
			{
				m_appPaused = true;
				m_minimized = true;
				m_maximized = false;
			}
			else if( in_wParam == SIZE_MAXIMIZED )
			{
				m_appPaused = false;
				m_minimized = false;
				m_maximized = true;
				OnResize();
			}
			else if( in_wParam == SIZE_RESTORED )
			{
				
				// Restoring from minimized state?
				if( m_minimized )
				{
					m_appPaused = false;
					m_minimized = false;
					OnResize();
				}
				// Restoring from maximized state?
				else if( m_maximized )
				{
					m_appPaused = false;
					m_maximized = false;
					OnResize();
				}
				else if( m_resizing )
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					OnResize();
				}
			}
		}

        return 0;
    }

    return 0;
}