#include "htAppD3D10.h"

#include <windows.h>

using namespace hooktail;

HRESULT
AppD3D10::InitAPI()
{
    HT_TRACE_IN();

    HRESULT hr = S_OK;

    UINT width  = 0;
    UINT height = 0;

    if (m_isWindowed)
    {
        RECT rc;
        GetClientRect(GetMainWindow(), &rc);
        width  = rc.right - rc.left;
        height = rc.bottom - rc.top;
    }
    else
    {
        // TODO@AMH add full-screen path changes
        RECT rc;
        GetClientRect(GetMainWindow(), &rc);
        width  = rc.right - rc.left;
        height = rc.bottom - rc.top;
    }

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd,sizeof(sd));

    sd.BufferDesc.Width         = width;
    sd.BufferDesc.Height        = height;
    sd.BufferDesc.Format        = m_backBufferFormat;
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
    sd.SampleDesc.Count         = m_msaaDesc.Count;
    sd.SampleDesc.Quality       = m_msaaDesc.Quality;

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

    if (SUCCEEDED(hr))
    {
        OnResize();
    }

    HT_TRACE_OUT();

    return hr;
}


HRESULT
AppD3D10::OnResize()
{
    HRESULT hr = S_OK;

    RELEASE(m_pBackBufferView);
    RELEASE(m_pDSView);
    RELEASE(m_pDSBuffer);


    // Resize the swap chain and recreate the render target view.

    hr = m_pSwapChain->ResizeBuffers(1, m_clientWidth, m_clientHeight, m_backBufferFormat, 0);


    // Create a RT View for the backbuffer
    ID3D10Texture2D* backBuffer;
    if (SUCCEEDED(hr))
    {
        hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer));
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD3dDevice->CreateRenderTargetView(backBuffer, 0, &m_pBackBufferView);
    }
    RELEASE(backBuffer);


    // Create the depth/stencil buffer and view.
    D3D10_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width          = m_clientWidth;
    depthStencilDesc.Height         = m_clientHeight;
    depthStencilDesc.MipLevels      = 1;
    depthStencilDesc.ArraySize      = 1;
    depthStencilDesc.Format         = m_dsFormat;
    depthStencilDesc.SampleDesc     = m_msaaDesc; // must match swap chain values.
    depthStencilDesc.Usage          = D3D10_USAGE_DEFAULT;
    depthStencilDesc.BindFlags      = D3D10_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0; 
    depthStencilDesc.MiscFlags      = 0;

    if (SUCCEEDED(hr))
    {
        hr = m_pD3dDevice->CreateTexture2D(&depthStencilDesc, 0, &m_pDSBuffer);
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD3dDevice->CreateDepthStencilView(m_pDSBuffer, 0, &m_pDSView);
    }

    // Bind the render target view and depth/stencil view to the pipeline.
    if (SUCCEEDED(hr))
    {
        m_pD3dDevice->OMSetRenderTargets(1, &m_pBackBufferView, m_pDSView);
    }


    // Set the viewport transform.

    D3D10_VIEWPORT vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width    = m_clientWidth;
    vp.Height   = m_clientHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;

    if (SUCCEEDED(hr))
    {
        m_pD3dDevice->RSSetViewports(1, &vp);
    }

    return hr;
}

VOID
AppD3D10::Render()
{
    m_pD3dDevice->ClearRenderTargetView(m_pBackBufferView, m_clearColor);
    m_pD3dDevice->ClearDepthStencilView(m_pDSView, D3D10_CLEAR_DEPTH, 1.0, 0);

    m_pSwapChain->Present(0,0);
}

HRESULT
AppD3D10::Update()
{
    return S_OK;
}


VOID
AppD3D10::InitApp()
{
    InitAPI();
}

/*
void
void
AppD3D10::Render()
{
    Draw();
}


LRESULT
AppD3D10::MsgProc(UINT in_msg, WPARAM in_wParam, LPARAM in_lParam)
{
    AppWindows::MsgProc(in_msg, in_wParam, in_lParam);

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




#define ReleaseCOM(x)           RELEASE(x)

int AppD3D10::Run()
{
    MSG msg = {0};

    mTimer.reset();

    while(msg.message != WM_QUIT)
    {
        // If there are Window messages then process them.
        if(PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        // Otherwise, do animation/game stuff.
        else
        {	
            mTimer.tick();

            if( !mAppPaused )
                updateScene(mTimer.getDeltaTime());	
            else
                Sleep(50);

            drawScene();
        }
    }
    return (int)msg.wParam;
}



HRESULT
AppD3D10::InitAPI()
{
    // Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width  = mClientWidth;
    sd.BufferDesc.Height = mClientHeight;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // No multisampling.
    sd.SampleDesc.Count   = 1;
    sd.SampleDesc.Quality = 0;

    sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount  = 1;
    sd.OutputWindow = mhMainWnd;
    sd.Windowed     = true;
    sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags        = 0;


    // Create the device.

    UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

    HR( D3D10CreateDeviceAndSwapChain(
        0,                 //default adapter
        md3dDriverType,
        0,                 // no software device
        createDeviceFlags, 
        D3D10_SDK_VERSION,
        &sd,
        &mSwapChain,
        &md3dDevice) );


    // The remaining steps that need to be carried out for d3d creation
    // also need to be executed every time the window is resized.  So
    // just call the onResize method here to avoid code duplication.

    onResize();
}

void
AppD3D10::OnResize()
{
    // Release the old views, as they hold references to the buffers we
    // will be destroying.  Also release the old depth/stencil buffer.

    ReleaseCOM(mRenderTargetView);
    ReleaseCOM(mDepthStencilView);
    ReleaseCOM(mDepthStencilBuffer);


    // Resize the swap chain and recreate the render target view.

    HR(mSwapChain->ResizeBuffers(1, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
    ID3D10Texture2D* backBuffer;
    HR(mSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer)));
    HR(md3dDevice->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView));
    ReleaseCOM(backBuffer);


    // Create the depth/stencil buffer and view.

    D3D10_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width     = mClientWidth;
    depthStencilDesc.Height    = mClientHeight;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count   = 1; // multisampling must match
    depthStencilDesc.SampleDesc.Quality = 0; // swap chain values.
    depthStencilDesc.Usage          = D3D10_USAGE_DEFAULT;
    depthStencilDesc.BindFlags      = D3D10_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0; 
    depthStencilDesc.MiscFlags      = 0;

    HR(md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
    HR(md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));


    // Bind the render target view and depth/stencil view to the pipeline.

    md3dDevice->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);


    // Set the viewport transform.

    D3D10_VIEWPORT vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width    = mClientWidth;
    vp.Height   = mClientHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;

    md3dDevice->RSSetViewports(1, &vp);
}


void
AppD3D10::AppD3D10()
{
    // Code computes the average frames per second, and also the 
    // average time it takes to render one frame.

    static int frameCnt = 0;
    static float t_base = 0.0f;

    frameCnt++;

    // Compute averages over one second period.
    if( (mTimer.getGameTime() - t_base) >= 1.0f )
    {
        float fps = (float)frameCnt; // fps = frameCnt / 1
        float mspf = 1000.0f / fps;

        std::wostringstream outs;   
        outs.precision(6);
        outs << L"FPS: " << fps << L"\n" 
            << "Milliseconds: Per Frame: " << mspf;
        mFrameStats = outs.str();

        // Reset for next average.
        frameCnt = 0;
        t_base  += 1.0f;
    }

}


void
AppD3D10::Draw()
{
    md3dDevice->ClearRenderTargetView(mRenderTargetView, mClearColor);
    md3dDevice->ClearDepthStencilView(mDepthStencilView, D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL, 1.0f, 0);
}


void
AppD3D10::Render()
{
}


LRESULT D3DApp::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg )
    {
        // WM_ACTIVATE is sent when the window is activated or deactivated.  
        // We pause the game when the window is deactivated and unpause it 
        // when it becomes active.  
    case WM_ACTIVATE:
        if( LOWORD(wParam) == WA_INACTIVE )
        {
            mAppPaused = true;
            mTimer.stop();
        }
        else
        {
            mAppPaused = false;
            mTimer.start();
        }
        return 0;

        // WM_SIZE is sent when the user resizes the window.  
    case WM_SIZE:
        // Save the new client area dimensions.
        mClientWidth  = LOWORD(lParam);
        mClientHeight = HIWORD(lParam);
        if( md3dDevice )
        {
            if( wParam == SIZE_MINIMIZED )
            {
                mAppPaused = true;
                mMinimized = true;
                mMaximized = false;
            }
            else if( wParam == SIZE_MAXIMIZED )
            {
                mAppPaused = false;
                mMinimized = false;
                mMaximized = true;
                onResize();
            }
            else if( wParam == SIZE_RESTORED )
            {

                // Restoring from minimized state?
                if( mMinimized )
                {
                    mAppPaused = false;
                    mMinimized = false;
                    onResize();
                }

                // Restoring from maximized state?
                else if( mMaximized )
                {
                    mAppPaused = false;
                    mMaximized = false;
                    onResize();
                }
                else if( mResizing )
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
                    onResize();
                }
            }
        }
        return 0;

        // WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
    case WM_ENTERSIZEMOVE:
        mAppPaused = true;
        mResizing  = true;
        mTimer.stop();
        return 0;

        // WM_EXITSIZEMOVE is sent when the user releases the resize bars.
        // Here we reset everything based on the new window dimensions.
    case WM_EXITSIZEMOVE:
        mAppPaused = false;
        mResizing  = false;
        mTimer.start();
        onResize();
        return 0;

        // WM_DESTROY is sent when the window is being destroyed.
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

        // The WM_MENUCHAR message is sent when a menu is active and the user presses 
        // a key that does not correspond to any mnemonic or accelerator key. 
    case WM_MENUCHAR:
        // Don't beep when we alt-enter.
        return MAKELRESULT(0, MNC_CLOSE);

        // Catch this message so to prevent the window from becoming too small.
    case WM_GETMINMAXINFO:
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200; 
        return 0;
    }

    return DefWindowProc(mhMainWnd, msg, wParam, lParam);
}


*/