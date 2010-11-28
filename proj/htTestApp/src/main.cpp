#include "htTestApp.h"

#include <stdio.h>

using hooktail::htTestApp;

int main()
{
    HT_TRACE_IN();

    htTestApp app;

    app.Run();

    HT_TRACE_OUT();

    return 0;
}