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

    virtual htApp*              CreateApp() = 0;
    virtual void                DestroyApp(htApp* in_pApp);

private:
    htAppFactory() {}
    virtual                     ~htAppFactory() {}
};

inline void
htAppFactory::DestroyApp(htApp* in_pApp)
{
    SAFE_DELETE(in_pApp);
}

