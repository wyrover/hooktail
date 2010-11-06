#pragma once

#include <windows.h>

#include "htFramework.h"

#define USE_PRINTF_FOR_LOGGING 1

// htFramwork-specific macros
#if USE_PRINTF_FOR_LOGGING
    #define HT_DEFINE_COMMON_DEBUG  0
    #define HT_LOG(x,...)           printf((x), __VA_ARGS__)
    #define HT_LOG_LVL(lvl,x,...)   printf((x), __VA_ARGS__)        
    #define HT_DBG(x,...)           printf((x), __VA_ARGS__)        
    #define HT_TRACE_IN()           printf("TRACE IN  -> %s()\n", __FUNCTION__)
    #define HT_TRACE_OUT()          printf("TRACE OUT <- %s()\n", __FUNCTION__)
    #define HT_TRACE(var)           do {} while (0) 
    #define HT_ASSERT(exp,...)      do {} while (0)
#else
    #define HT_APP_FW               m_fw
    #define HT_LOG(x)               _HT_LOG(x)
    #ifdef HT_DEBUG
        #define HT_DEFINE_COMMON_DEBUG  1
        // LOGGING
        #define HT_TRACE_IN()           _HT_DBG_TRACE_IN(HT_APP_FW)
        #define HT_TRACE_OUT()          _HT_DBG_TRACE_OUT(HT_APP_FW)
        #define HT_TRACE(var)           _HT_DBG_TRACE(HT_APP_FW, var)
        // DEBUG
        #define HT_DBG(level, ...)      _HT_DBG_LOG(HT_APP_FW, level, __VA_ARGS__)
        #define HT_ASSERT(exp, ...)     if(!(exp)) { _HT_LOG(HT_APP_FW, "ASSERT!: ", ...); assert(exp); }
    #else
        #define HT_DEFINE_COMMON_DEBUG  0
        #define HT_LOG          
        #define HT_DBG          
        #define HT_TRACE_IN     
        #define HT_TRACE_OUT    
        #define HT_TRACE        
        #define HT_ASSERT       
    #endif // HT_DEBUG
#endif // USE_PRINTF_FOR_LOGGING

// namespace ht {

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

//     VOID                        Log(const CHAR* in_msg, ...);
//     VOID                        DbgLog(const CHAR* in_msg, ...);
//     VOID                        DbgLog(htLogger::HT_LOG_LEVEL in_level, const CHAR* in_msg, ...);

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
//    htAppOptions                m_appOptions;

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
    htLogger log = m_fw.GetLogger();

    log.Log("test!!!\n");
    m_fw.GetLogger().IncTab();

    m_appTitle  = L"Basic HT Application";
    m_appDesc   = L"A Hooktail Framework Application";

    m_fw.GetLogger().DecTab();
    m_fw.GetLogger().Log("HT_TRACE %s>> In  %s()\n", __FUNCTION__);
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
// 
// 

// } // namespace ht

