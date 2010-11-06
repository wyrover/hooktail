#pragma once

#include "htFileLogger.h"

#include <windows.h>

#define HTLOGGER_TAB_SIZE       1024

class htLogger
{
public:

    typedef enum _HT_LOG_LEVEL
    {
        HT_LOG_LEVEL_NONE = 0,
        HT_LOG_LEVEL_CRITICAL,
        HT_LOG_LEVEL_ERROR,
        HT_LOG_LEVEL_WARNING,
        HT_LOG_LEVEL_NOTICE,
        HT_LOG_LEVEL_INFO,
        HT_LOG_LEVEL_TRACE,
        ///
        HT_NUM_LOG_LEVELS
    } HT_LOG_LEVEL;

    typedef enum _HT_LOG_OUTPUT
    {
        HT_LOG_OUTPUT_FILE = 0,
        HT_LOG_OUTPUT_CONSOLE,
        HT_LOG_OUTPUT_ALL,
        HT_LOG_OUTPUT_NONE,
        ///
        HT_NUM_LOG_OUTPUTS
    } HT_LOG_OUTPUT;

                                htLogger() : m_tabSize(0) { m_tabStr[0] = '\0'; }
    virtual                     ~htLogger() {}

    VOID                        LogVA(HT_LOG_LEVEL in_level, const CHAR*, va_list in_vaList);
    VOID                        LogVA(const CHAR*, va_list in_vaList);
    VOID                        Log(HT_LOG_LEVEL in_level, const CHAR* in_msg, ...);
    VOID                        Log(const CHAR*, ...);

    VOID                        SetDbgLevel(HT_LOG_LEVEL in_level) { m_logLevel = in_level; }
    VOID                        SetLogOuput(HT_LOG_OUTPUT in_output) { m_logOutput = in_output; }

    const HT_LOG_LEVEL&         GetDbgLevel() const { return m_logLevel; }
    const HT_LOG_OUTPUT&        GetLogOutput() const { return m_logOutput; }

    static const CHAR*          GetLogLevelName(HT_LOG_LEVEL in_level);

    VOID                        IncTab() { ++m_tabSize; ++m_tabSize; memset(m_tabStr, ' ', m_tabSize); m_tabStr[m_tabSize] = '\0'; }
    VOID                        DecTab() { --m_tabSize; --m_tabSize; memset(m_tabStr, ' ', m_tabSize); m_tabStr[m_tabSize] = '\0'; }

    const CHAR*                 GetTab() const { return m_tabStr; }

private:

    VOID                        LogText(const CHAR* in_text);

    VOID                        LogFile(const CHAR* in_text);
    VOID                        LogConsole(const CHAR* in_text);

    HT_LOG_LEVEL                m_logLevel;
    HT_LOG_OUTPUT               m_logOutput;

    UINT                        m_tabSize;
    char                        m_tabStr[HTLOGGER_TAB_SIZE];

    htFileLogger                m_fileLogger;

    static const UINT           s_bufSize;
};


inline VOID
htLogger::LogConsole(const CHAR* in_text)
{
    printf("LOG %s\n", in_text);
}

inline VOID
htLogger::LogFile(const CHAR* in_text)
{
    printf("LOG FILE %s\n", in_text);
    //m_fileLogger.Log(in_text);
}
