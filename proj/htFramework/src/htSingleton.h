#pragma once

namespace hooktail
{

template <class T>
class htSingleton
{

public:

    static T& Instance()
    {
        static T s_theInstance;
        
        return s_theInstance;
    }

protected:

    htSingleton();
    ~htSingleton();
    
private:
}; // htSingleton

} // namespace hooktail