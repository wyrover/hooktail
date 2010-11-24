#pragma once

#include <stdio.h>

namespace hooktail
{

    FILE*                       htFileOpen(const char* in_path, const char* in_mode);
    bool                        htFileOpen(FILE* in_file);

    template<class T>
    void htSwap(T& a, T& b)
    {
        T copy(a);
        a = b;
        b = copy;
    }

} // namespace hooktail
