#pragma once 

// includes, framework
#include "htUtility.h"
#include "htCommon.h"
#include "htSingleton.h"
#include "htLogger.h"
#include "htTimer.h"
#include "htColor.h"
#include "htVector3.h"

// macros
#define HT_LOG(x, ...)                          GetLogger().Log((x), __VA_ARGS__)
#define HT_LOG_LVL(level,x,...)                 GetLogger().Log(level, (x), __VA_ARGS__)        

// internal debug macros
#if _DEBUG
#define _HT_DBG_TRACE_IN()                      GetLogger().Log(hooktail::HT_LOG_LEVEL_TRACE, "HT_TRACE %s>> In  %s()\n", \
                                                GetLogger().GetTab(), __FUNCTION__); \
                                                GetLogger().IncTab()

#define _HT_DBG_TRACE_OUT()                     GetLogger().DecTab(); \
                                                GetLogger().Log(hooktail::HT_LOG_LEVEL_TRACE, "HT_TRACE %s<< Out %s()\n", \
                                                GetLogger().GetTab(), __FUNCTION__)

#define _HT_DBG_TRACE(var)                      GetLogger().Log(hooktail::HT_LOG_LEVEL_TRACE, "HT_TRACE %s:  %s\n", \
                                                GetLogger().GetTab(), TOSTRING(var)) // TODO @amh Add variable arg printing

#define _HT_DBG_LOG(level, __VA_ARGS__)         GetLogger().Log(level, ...)

// LOGGING
#define HT_TRACE_IN()                           _HT_DBG_TRACE_IN()
#define HT_TRACE_OUT()                          _HT_DBG_TRACE_OUT()
#define HT_TRACE(var)                           _HT_DBG_TRACE(var)
// DEBUG
#define HT_DBG(level, ...)                      _HT_DBG_LOG(level, __VA_ARGS__)
#else
#define HT_TRACE_IN()                           do {} while (0) 
#define HT_TRACE_OUT()                          do {} while (0) 
#define HT_TRACE(var)                           do {} while (0) 
#define HT_DBG(x,...)                           do {} while (0) 
#endif // _DEBUG 


static hooktail::htLogger&
GetLogger()
{   
    return hooktail::htSingleton<hooktail::htLogger>::Instance();
}

namespace hooktail
{

class htFramework
{
public:

                                htFramework();
    virtual                     ~htFramework() {}

    // debug logging
    VOID                        SetDbgLevel(HT_LOG_LEVEL in_level) { GetLogger().SetDbgLevel(in_level); }
    VOID                        SetLogOuput(HT_LOG_OUTPUT in_output) { GetLogger().SetLogOuput(in_output); }
    const HT_LOG_LEVEL          GetDbgLevel() const { return GetLogger().GetDbgLevel(); }
    const HT_LOG_OUTPUT         GetLogOutput() const { return GetLogger().GetLogOutput(); }

    // timer
    VOID                        TimerStart() { m_timer.Start(); }
    VOID                        TimerStop() { m_timer.Stop(); }
    VOID                        TimerReset() { m_timer.Reset(); }
    const double                GetElapsedTime() const { m_timer.GetElapsedTime(); }


private:

    BOOL                        m_loggingEnabled;           /// Enable application logging
    BOOL                        m_dbgLoggingEnabled;        /// Enable application debug logging

    htTimer                     m_timer;                    /// HT Framework timer
};

inline
htFramework::htFramework()
    : m_loggingEnabled(FALSE)
    , m_dbgLoggingEnabled(FALSE)
{
#if _DEBUG
    GetLogger().SetDbgLevel(HT_LOG_LEVEL_INFO);
    GetLogger().SetLogOuput(HT_LOG_OUTPUT_CONSOLE);
#else
    GetLogger().SetDbgLevel(HT_LOG_LEVEL_NONE);
    GetLogger().SetLogOuput(HT_LOG_OUTPUT_NONE);
#endif
}

} // namespace hooktail
