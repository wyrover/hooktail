#pragma once

/*
===============================================================================

    htAppFactory

    Used to create an instance of an htApp

===============================================================================
*/

class htAppFactory
{
public:
                                htAppFactory() {}
    virtual                     ~htAppFactory() {}

    virtual htApp*              CreateApp() = 0;
    virtual void                DestroyApp(htApp* in_pApp);
};

inline void
htAppFactory::DestroyApp(htApp* in_pApp)
{
    SAFE_DELETE(in_pApp);
}

