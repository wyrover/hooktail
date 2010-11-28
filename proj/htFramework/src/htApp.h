#pragma once

#include <windows.h>

#include "htFramework.h"

namespace hooktail {

class App
{
public:

    typedef struct _AppOptions
    {
    } AppOptions;

                                App();
    virtual                     ~App() {}

    virtual VOID                InitFramework();

    const std::wstring&         GetAppTitle();
    const std::wstring&         GetAppDesc();

    VOID                        TimerStart() { m_fw.TimerStart(); }
    VOID                        TimerStop() { m_fw.TimerStop(); }
    VOID                        TimerReset() { m_fw.TimerReset(); }

protected:

    VOID                        InitApp();

    VOID                        SetAppTitle(const std::wstring in_title);
    VOID                        SetAppDesc(const std::wstring in_desc);
    VOID                        SetDbgLevel(HT_LOG_LEVEL in_level) { m_fw.SetDbgLevel(in_level); }

    std::wstring                m_appTitle;                 /// Application title
    std::wstring                m_appDesc;                  /// Application description

private:

    htFramework                 m_fw;
    AppOptions                  m_appOptions;

};

inline
App::App()
{
    // Framework Initialization
    InitFramework();

    // App-specific initialization
    InitApp();
}

inline VOID
App::InitFramework()
{
    HT_TRACE_IN();

#if _DEBUG
    m_fw.SetDbgLevel(HT_LOG_LEVEL_TRACE);
#else
    m_fw.SetDbgLevel(HT_LOG_LEVEL_NONE);
#endif

    HT_TRACE_OUT();
}

inline VOID
App::InitApp()
{
    HT_TRACE_IN();

    m_appTitle  = L"Basic HT Application";
    m_appDesc   = L"A Hooktail Framework Application";

    HT_TRACE_OUT();
}


inline VOID
App::SetAppTitle(const std::wstring in_title)
{
    HT_TRACE_IN();

    m_appTitle = in_title;

    HT_TRACE_OUT();
}

inline VOID
App::SetAppDesc(const std::wstring in_desc)
{
    HT_TRACE_IN();

    m_appDesc = in_desc;

    HT_TRACE_OUT();
}

inline const std::wstring&
App::GetAppTitle()
{
    return m_appTitle;
}

inline const std::wstring&
App::GetAppDesc()
{
    return m_appDesc;
}

} // namespace hooktail

