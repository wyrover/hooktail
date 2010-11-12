#pragma once

#include <windows.h>

#include "htFramework.h"

namespace hooktail {

class htApp
{
public:

    typedef struct _htAppOptions
    {
    } htAppOptions;

                                htApp();
    virtual                     ~htApp() {}

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
    VOID                        SetDbgLevel(htLogger::HT_LOG_LEVEL in_level) { m_fw.SetDbgLevel(in_level); }

    std::wstring                m_appTitle;                 /// Application title
    std::wstring                m_appDesc;                  /// Application description

private:

    htFramework                 m_fw;
    htAppOptions                m_appOptions;

};

inline
htApp::htApp()
{
    // Framework Initialization
    InitFramework();

    // App-specific initialization
    InitApp();
}

inline VOID
htApp::InitFramework()
{
#if _DEBUG
    m_fw.SetDbgLevel(htLogger::HT_LOG_LEVEL_TRACE);
#else
    m_fw.SetDbgLevel(htLogger::HT_LOG_LEVEL_NONE);
#endif
}

inline VOID
htApp::InitApp()
{
    HT_TRACE_IN();

    m_appTitle  = L"Basic HT Application";
    m_appDesc   = L"A Hooktail Framework Application";

    HT_TRACE_OUT();
}


inline VOID
htApp::SetAppTitle(const std::wstring in_title)
{
    //DbgLog(htLogger::HT_LOG_LEVEL_TRACE, __FUNCTION__);
    m_appTitle = in_title;
}

inline VOID
htApp::SetAppDesc(const std::wstring in_desc)
{
    //DbgLog(htLogger::HT_LOG_LEVEL_TRACE, __FUNCTION__);
    m_appDesc = in_desc;
}

inline const std::wstring&
htApp::GetAppTitle()
{
    return m_appTitle;
}

inline const std::wstring&
htApp::GetAppDesc()
{
    return m_appDesc;
}

// inline VOID
// htApp::Log(const CHAR* in_msg, ...)
// {
//     va_list vl;
//     va_start(vl, in_msg);
//     m_fw.m_log.LogVA(in_msg, vl);
//     va_end(vl);
// }
// 
// inline VOID
// htApp::DbgLog(const CHAR* in_msg, ...)
// {
// #if _DEBUG
//     va_list vl;
//     va_start(vl, in_msg);
//     m_fw.m_log.LogVA(in_msg, vl);
//     va_end(vl);
// #endif
// }
// 
// inline VOID
// htApp::DbgLog(htLogger::HT_LOG_LEVEL in_level, const CHAR* in_msg, ...)
// {
// #if _DEBUG
//     va_list vl;
//     va_start(vl, in_msg);
//     m_fw.m_log.LogVA(in_level, in_msg, vl);
//     va_end(vl);
// #endif
// }



} // namespace hooktail

