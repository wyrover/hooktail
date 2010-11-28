#pragma once

#include "htApp.h"
#include <windows.h>

namespace hooktail
{

class AppWindows : public App
{
public:

                                AppWindows();

    HINSTANCE                   GetInstance() { return m_hInstance; }
    HWND                        GetMainWindow() { return m_hMainWnd; }

    virtual LRESULT             MsgProc(UINT in_msg, WPARAM in_wParam, LPARAM in_lParam);
    static LRESULT CALLBACK     WindowProc(HWND in_hwnd, UINT in_msg, WPARAM in_wParam, LPARAM in_lParam);


    int                         Run();

    virtual VOID                OnResize() {}

protected:


    BOOL                        m_minimized;
    BOOL                        m_maximized;
    BOOL                        m_resizing;
    BOOL                        m_appPaused;

    UINT                        m_clientWidth;
    UINT                        m_clientHeight;

private:

    int                         GetConsoleHandle();
    int                         InitWindow();

    HINSTANCE                   m_hInstance;
    HWND                        m_hMainWnd;

    std::wstring                m_wndClassName;
};


/*
===============================================================================

    htAppWindowsFactory

    Used to create an instance of an htApp

===============================================================================
*/
class AppWindowsFactory
{
public:
                                AppWindowsFactory() {}
    virtual                     ~AppWindowsFactory() {}

    virtual AppWindows*         CreateApp() = 0;
    virtual void                DestroyApp(AppWindows* in_pApp);
};

inline void
AppWindowsFactory::DestroyApp(AppWindows* in_pApp)
{
    SAFE_DELETE(in_pApp);
}

} // namespace hooktail