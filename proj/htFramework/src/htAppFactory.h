#pragma once

/*
===============================================================================

    htAppFactory

    Used to create an instance of an htApp

===============================================================================
*/

class AppFactory
{
public:

    virtual App*                CreateApp() = 0;
    virtual void                DestroyApp(App* in_pApp);

private:
    AppFactory() {}
    virtual                     ~AppFactory() {}
};

inline void
AppFactory::DestroyApp(App* in_pApp)
{
    SAFE_DELETE(in_pApp);
}

