#include "htAppD3D.h"

LRESULT
htAppD3D::MsgProc(UINT in_msg, WPARAM in_wParam, LPARAM in_lParam)
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
