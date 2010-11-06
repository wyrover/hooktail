#pragma once


#ifdef _DEBUG
#define HT_DEBUG
#include <cassert>
#endif // _DEBUG

#define _UNIQUE(x, y)           x##y
#define _UNIQUENAME(x, y)       _UNIQUE(x, y)
#define UNIQUE(x)               _UNIQUE(__unique_name_,x)
#define UNIQUENAME(x)           _UNIQUENAME(x, __LINE__)

#define TOSTRING( x )           #x

#define SAFE_DELETE(x) { if(x) { delete (x); (x) = NULL; } }

// Compile-time so always enabled
#define STATIC_ASSERT(exp)      typedef char UNIQUE(__LINE__)[(exp)?1:-1];


///////////////////////////////////////////////////////////////////////////////
//
// Hootkail specific Macros
//
///////////////////////////////////////////////////////////////////////////////

#define HT_FAIL         0
#define HT_SUCCESS      1

#define HT_DEFAULT_APP_WINDOW_WIDTH     800
#define HT_DEFAULT_APP_WINDOW_HEIGHT    600


