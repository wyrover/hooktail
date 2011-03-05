#pragma once

#include <windows.h>

#define _UNIQUE(x, y)           x##y
#define _UNIQUENAME(x, y)       _UNIQUE(x, y)
#define UNIQUE(x)               _UNIQUE(__unique_name_,x)
#define UNIQUENAME(x)           _UNIQUENAME(x, __LINE__)

#define TOSTRING( x )           #x

#define SAFE_DELETE(x)          { if(x) { delete (x); (x) = NULL; } }

#define UNUSED_ARG(x)           (void) (x)

#define STATIC_ASSERT(exp)      typedef char UNIQUE(__LINE__)[(exp)?1:-1];

#define ARRAY_SIZE(x)           (sizeof((x)) / sizeof((x)[0]))


///////////////////////////////////////////////////////////////////////////////
//
// Hooktail specific Macros
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define HT_DEBUG
#include <cassert>
#define HT_ASSERT(x)            assert((x))
#define HT_ASSERT_STR(x, str, ...) if (!(x)) printf(str, __VA_ARGS__); HT_ASSERT((x))
#define HT_INLINE               
#else
#define HT_ASSERT(x)            do {} while (0)
#define HT_ASSERT_STR(x, str, ...) HT_ASSERT((x))
#define HT_INLINE               __forceinline
#endif // _DEBUG

#define RELEASE(x)              { if (x) { (x)->Release(); x = 0; } }

#define HT_FAIL                 0
#define HT_SUCCESS              1

#define HT_DEFAULT_APP_WINDOW_WIDTH     800
#define HT_DEFAULT_APP_WINDOW_HEIGHT    600


