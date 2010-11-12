#pragma once 

#include <iostream>
#include <fstream>
#include <windows.h>

namespace hooktail
{

class htFileLogger
{
public:
                            htFileLogger() {}
//                            htFileLogger(const std::string in_filename) { m_filename = in_filename; }
                            ~htFileLogger() {}
    VOID                    Log(const CHAR* str);

    const CHAR*             GetFileName() { return m_filename.c_str(); }

private:

    std::string             m_filename;
    std::fstream            m_file;

};
} // namespace hooktail
