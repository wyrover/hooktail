#pragma once

// define types here :^)

#define HT_FAIL         0
#define HT_SUCCESS      1

#define SAFE_DELETE(x) { if(x) { delete (x); (x) = NULL; } }

#define HT_DEFAULT_APP_WINDOW_WIDTH     800
#define HT_DEFAULT_APP_WINDOW_HEIGHT    600

