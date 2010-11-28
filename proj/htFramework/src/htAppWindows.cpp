#include "htAppWindows.h"
#include <windows.h>

using namespace hooktail;

AppWindows::AppWindows()
    : App()
    , m_hInstance(NULL)
    , m_hMainWnd(NULL)
    , m_minimized(FALSE)
    , m_maximized(FALSE)
    , m_resizing(FALSE)
    , m_appPaused(FALSE)
    , m_clientWidth(HT_DEFAULT_APP_WINDOW_WIDTH)
    , m_clientHeight(HT_DEFAULT_APP_WINDOW_HEIGHT)
    , m_wndClassName(L"htAppWindowsClass")
{
    if( !GetConsoleHandle() )
    {
        HT_LOG("Failed to get console window handle");
    }
    else
    {
        InitWindow();
    }
}


int
AppWindows::GetConsoleHandle()
{
    TCHAR   origWindowTitle[MAX_PATH];
    TCHAR   uniqueWindowTitle[MAX_PATH];
    HWND    consoleHwnd;

    // How to get the handle to console window from MSDN (http://support.microsoft.com/kb/124103)
    //
    //   1. Call GetConsoleTitle() to save the current console window title.
    //   2. Call SetConsoleTitle() to change the console title to a unique title.
    //   3. Call Sleep(40) to ensure the window title was updated.
    //   4. Call FindWindow(NULL, uniquetitle), to obtain the HWND this call returns the HWND -- or NULL if the operation failed.
    //   5. Call SetConsoleTitle() with the value retrieved from step 1, to restore the original window title. 

    wsprintf(uniqueWindowTitle, TEXT("%d/%d"),
             GetTickCount(),
             GetCurrentProcessId());


    if( !GetConsoleTitle(origWindowTitle, MAX_PATH) )
    {
        HT_LOG("Could not get console title");
        return HT_FAIL;
    }

    if( !SetConsoleTitle(uniqueWindowTitle) )
    {
        HT_LOG("Could not set unique console title");
        return HT_FAIL;
    }
    
    Sleep(40);

    consoleHwnd = FindWindow(NULL, uniqueWindowTitle);

    if (NULL == consoleHwnd)
    {
        HT_LOG("Could not get HWND to console window");
        return HT_FAIL;
    }

    if( !SetConsoleTitle(origWindowTitle) )
    {
        HT_LOG("Could not set original console title back");
        return HT_FAIL;
    }

#ifdef __WIN64
    m_hInstance = (HINSTANCE)GetWindowLongPtr(consoleHwnd, GWLP_HINSTANCE);
#else
    m_hInstance = (HINSTANCE)GetWindowLong(consoleHwnd, GWL_HINSTANCE);
#endif

/*
    if (NULL == m_hInstance)
    {
        HT_LOG("Could not get HINSTANCE to console window");
        return HT_FAIL;
    }
 */

    return HT_SUCCESS;
}

int
AppWindows::InitWindow()
{
    // Create a Windows class description and initialize it
    WNDCLASSEX wcx = {};

    wcx.cbSize          = sizeof(wcx);                          /// size of structure 
    wcx.style           = CS_HREDRAW | CS_VREDRAW;              /// redraw if size changes 
    wcx.lpfnWndProc     = AppWindows::WindowProc;             /// points to window procedure 
    wcx.cbClsExtra      = NULL;                                 /// no extra class memory 
    wcx.cbWndExtra      = NULL;                                 /// no extra window memory 
    wcx.hInstance       = m_hInstance;                          /// handle to instance 
    wcx.hIcon           = LoadIcon(NULL, IDI_APPLICATION);      /// predefined app. icon 
    wcx.hCursor         = LoadCursor(NULL, IDC_ARROW);          /// predefined arrow 
    wcx.hbrBackground   = (HBRUSH)GetStockObject(WHITE_BRUSH);  /// white background brush 
    wcx.lpszMenuName    = NULL;                                 /// name of menu resource 
    wcx.lpszClassName   = m_wndClassName.c_str();               /// name of window class 
    
    // Register the class
	if( !RegisterClassEx(&wcx) )
	{
        HT_LOG("RegisterClassEx failed");
        return 1;
	}

    RECT R = { 0, 0, m_clientWidth, m_clientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

    // Create the window
    m_hMainWnd = CreateWindow(
        m_wndClassName.c_str(),
        GetAppTitle().c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        0,
        0,
        m_hInstance,
        0);

    if( NULL == m_hMainWnd )
	{
        HT_LOG("CreateWindow failed.");
        return 1;
	}

    ShowWindow (m_hMainWnd, SW_SHOW);
    UpdateWindow(m_hMainWnd);

    return 0;
}

int
AppWindows::Run()
{
    MSG     msg     = {0};
    BOOL    bRet    = 1;

    while( 0 != (bRet = GetMessage(&msg, 0, 0, 0)) )
    {
        if( -1 == bRet )
        {
            HT_LOG("GetMessage Failed");
            return FALSE;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

LRESULT
AppWindows::MsgProc(UINT in_msg, WPARAM in_wParam, LPARAM in_lParam)
{

    // @AMH TODO
    // Handle the retuned LRESULT values properly for this and all
    // virtual definitions of this procedure

    switch(in_msg)
    {
	// WM_ACTIVATE is sent when the window is activated or deactivated.  
	// We pause the game when the window is deactivated and unpause it 
	// when it becomes active.  
	case WM_ACTIVATE:
		if( LOWORD(in_wParam) == WA_INACTIVE )
		{
			m_appPaused = true;
			TimerStop();
		}
		else
		{
			m_appPaused = false;
			TimerStart();
		}
		return 0;

	// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		return 0;

	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		m_appPaused = true;
		m_resizing  = true;
        TimerStop();
		return 0;

	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		m_appPaused = false;
		m_resizing  = false;
		TimerStart();
		OnResize();
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
		((MINMAXINFO*)in_lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)in_lParam)->ptMinTrackSize.y = 200; 
		return 0;
    default:
        return 0;
	}
}

LRESULT CALLBACK
AppWindows::WindowProc(HWND in_hwnd, UINT in_msg, WPARAM in_wParam, LPARAM in_lParam)
{
    static AppWindows* pApp;
    //__try
    {
        switch( in_msg )
	    {
            //HANDLE_MSG(in_hwnd, WM_CREATE, OnCreate);
		    case WM_CREATE:
		    {

                // Get the 'this' pointer we passed to CreateWindow via the lpParam parameter.
			    CREATESTRUCT* cs = (CREATESTRUCT*)in_lParam;
			    pApp = (AppWindows*)cs->lpCreateParams;
			    return 0;
            }
        }

	    // Don't start processing messages until after WM_CREATE.
	    if( pApp )
        {
		    return pApp->MsgProc(in_msg, in_wParam, in_lParam);
        }
	    else
        {
		    return DefWindowProc(in_hwnd, in_msg, in_wParam, in_lParam);
        }
    }
    //__except (filter-expression /* evaluate filter */) 
    //{
    //    // exception handler block 
    //}		

}

