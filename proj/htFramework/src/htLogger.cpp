#include "htCommon.h"
#include "htLogger.h"
#include "htDefine.h"

using namespace hooktail;

// Init const data
const UINT htLogger::s_bufSize = 1024;

VOID
htLogger::Log(const CHAR* in_text, ...)
{
    va_list val;
	va_start(val, in_text);
	LogVA(in_text, val);
	va_end(val);
}

VOID
htLogger::Log(HT_LOG_LEVEL in_level, const CHAR* in_text, ...)
{
    if(in_level <= m_logLevel)
    {
        std::string str;
        va_list val;
        
        str = "[";
        str += GetLogLevelName(in_level);
        str += "]:\t";
        str += in_text;

	    va_start(val, in_text);
    	LogVA(str.c_str(), val);
        va_end(val);
    }
}

VOID
htLogger:: LogVA(const CHAR* in_text, va_list in_vaList)
{
    static CHAR s_pBuf[s_bufSize];

	vsprintf_s(s_pBuf, s_bufSize, in_text, in_vaList);

    LogText(s_pBuf);
}

VOID
htLogger:: LogVA(HT_LOG_LEVEL in_level, const CHAR* in_text, va_list in_vaList)
{
    if(in_level <= m_logLevel)
    {
        static CHAR s_pBuf[s_bufSize];
        std::string str;
        
        str = "[";
        str += GetLogLevelName(in_level);
        str += "]:\t";
        str += in_text;

        vsprintf_s(s_pBuf, s_bufSize, str.c_str(), in_vaList);
        
        LogText(s_pBuf);
    }
}


VOID
htLogger::LogText(const CHAR* in_text)
{
//     static CHAR s_pBuf[s_bufSize];
//     std::string str;
// 
//     str = m_tabStr;
//     str += in_text';

    switch(m_logOutput)
    {
    case HT_LOG_OUTPUT_FILE:
        LogFile(in_text);
        break;
    case HT_LOG_OUTPUT_CONSOLE:
        LogConsole(in_text);
        break;
    case HT_LOG_OUTPUT_ALL:
        LogConsole(in_text);
        LogFile(in_text);
        break;
    case HT_LOG_OUTPUT_NONE:
    default:
        break;
    }
}


const CHAR*
htLogger::GetLogLevelName(HT_LOG_LEVEL in_level)
{
    switch(in_level)
    {
    case HT_LOG_LEVEL_CRITICAL:
        return "HT_CRITICAL";
    case HT_LOG_LEVEL_ERROR:
        return "HT_ERROR";
    case HT_LOG_LEVEL_WARNING:
        return "HT_WARNING";
    case HT_LOG_LEVEL_INFO:
        return "HT_INFO";
    case HT_LOG_LEVEL_TRACE:
        return "HT_TRACE";
    case HT_LOG_LEVEL_NONE:
        return "HT_NONE";
    default:
        HT_ASSERT(!"HT_LOG_LEVEL not found");
        return "";
    }
}