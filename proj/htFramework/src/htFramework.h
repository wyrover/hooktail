#pragma once 


// internal macros
#define _HT_LOG(fw, x)                          (fw).GetLogger().Log((x));

// internal debug macros
#if _DEBUG
#define _HT_DBG_TRACE_IN(fw)                    (fw).GetLogger().Log("HT_TRACE %s>> In  %s()\n", (fw).GetLogger().GetTab(), __FUNCTION__); (fw).GetLogger().IncTab()
#define _HT_DBG_TRACE_OUT(fw)                   (fw).GetLogger().Log("HT_TRACE %s<< Out %s()\n", (fw).GetLogger().GetTab(), __FUNCTION__); (fw).GetLogger().DecTab()
#define _HT_DBG_TRACE(fw, var)                  (fw).GetLogger().Log("HT_TRACE %s:  %s\n", (fw).GetLogger().GetTab(), TOSTRING(var)) // TODO @amh Add variable arg printing
#define _HT_DBG_LOG(fw, level, __VA_ARGS__)     (fw).GetLogger().Log(level, ...)
#endif // _DEBUG 

// includes, framework
#include "htCommon.h"
#include "htTimer.h"
#include "htLogger.h"


class htFramework
{
public:

                                htFramework();
    virtual                     ~htFramework() {}

    VOID                        SetDbgLevel(htLogger::HT_LOG_LEVEL in_level) { m_log.SetDbgLevel(in_level); }
    VOID                        SetLogOuput(htLogger::HT_LOG_OUTPUT in_output) { m_log.SetLogOuput(in_output); }

    const htLogger::HT_LOG_LEVEL    GetDbgLevel() const { return m_log.GetDbgLevel(); }
    const htLogger::HT_LOG_OUTPUT   GetLogOutput() const { return m_log.GetLogOutput(); }

    VOID                        TimerStart() { m_timer.Start(); }
    VOID                        TimerStop() { m_timer.Stop(); }
    VOID                        TimerReset() { m_timer.Reset(); }

    VOID                        Log(const CHAR* in_msg, ...);
    VOID                        DbgLog(const CHAR* in_msg, ...);
    VOID                        DbgLog(htLogger::HT_LOG_LEVEL in_level, const CHAR* in_msg, ...);

    const double                GetElapsedTime() const { m_timer.GetElapsedTime(); }

    htLogger                    GetLogger() { return m_log; }
    htTimer                     GetTimer() { return m_timer; }

private:

    BOOL                        m_loggingEnabled;           /// Enable application logging
    BOOL                        m_dbgLoggingEnabled;        /// Enable application debug logging

    htLogger                    m_log;                      /// HT Framework logger
    htTimer                     m_timer;                    /// HT Framework timer
    
    friend class                htApp;
};

inline
htFramework::htFramework()
    : m_loggingEnabled(FALSE)
    , m_dbgLoggingEnabled(FALSE)
{
#if _DEBUG
    m_log.SetDbgLevel(htLogger::HT_LOG_LEVEL_INFO);
    m_log.SetLogOuput(htLogger::HT_LOG_OUTPUT_CONSOLE);
#else
    m_log.SetDbgLevel(htLogger::HT_LOG_LEVEL_NONE);
    m_log.SetLogOuput(htLogger::HT_LOG_OUTPUT_NONE);
#endif
}
/*
inline VOID
htFramework::Log(const CHAR* in_msg, ...)
{
    va_list vl;
    va_start(vl, in_msg);
    m_log.LogVA(in_msg, vl);
    va_end(vl);
}

inline VOID
htFramework::DbgLog(const CHAR* in_msg, ...)
{
#if _DEBUG
    va_list vl;
    va_start(vl, in_msg);
    m_log.LogVA(m_log.GetDbgLevel(), in_msg, vl);
    va_end(vl);
#endif
}

inline VOID
htFramework::DbgLog(htLogger::HT_LOG_LEVEL in_level, const CHAR* in_msg, ...)
{
#if _DEBUG
    va_list vl;
    va_start(vl, in_msg);
    m_log.LogVA(in_level, in_msg, vl);
    va_end(vl);
#endif
}
*/