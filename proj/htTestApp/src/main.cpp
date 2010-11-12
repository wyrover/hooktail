
#include "htFramework.h"
#include "htTestApp.h"

#include <stdio.h>

using hooktail::htFramework;
using hooktail::htTimer;
using hooktail::htTestApp;

int main()
{
    HT_TRACE_IN();

    htTestApp app;

    app.Run();

    HT_TRACE_OUT();

    return 0;
}