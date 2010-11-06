#pragma once

// define types here :^)

#define HT_FAIL         0
#define HT_SUCCESS      1

#if _DEBUG
#include <assert.h>
#define HT_ASSERT(x,y) { if(!(x)) { printf("ASSERT: %s\n", y); } assert(x); }
#else
#define HT_ASSERT(x,y) do {} while (0)
#endif

#define SAFE_DELETE(x) { if(x) { delete (x); (x) = NULL; } }

#define HT_DEFAULT_APP_WINDOW_WIDTH     800
#define HT_DEFAULT_APP_WINDOW_HEIGHT    600

#define HT_TRACE_IN() DbgLog(htLogger::HT_LOG_LEVEL_TRACE, __FUNCTION__)

