#pragma once

#include "htPoint.h"

// #include <iostream>
// 
// using std::ostream;

namespace hooktail
{

template<typename Type>
class BoundingBox
{
public:
    BoundingBox() {}
    BoundingBox(Point<Type>& in_min, Point<Type>& in_max) : m_min(in_min), m_max(in_max) {}
    BoundingBox(const BoundingBox<Type>& in_bb) : m_min(in_bb.m_min), m_max(in_bb.m_max) {}

    BoundingBox&                        operator=(const BoundingBox& in_bb);

    Type                        GetWidth() { return m_max.X() - m_min.X(); }
    Type                        GetHeight() { return m_max.Y() - m_min.Y(); }
    Type                        GetDepth() { return m_max.Z() - m_min.Z(); }

    friend ostream&             operator<<(ostream& os, const BoundingBox& in_bb);

private:
    Point<Type>                 m_min;
    Point<Type>                 m_max;
};

template<typename Type>
HT_INLINE BoundingBox<Type>& BoundingBox<Type>::operator=(const BoundingBox& in_bb)
{
    if(this == &in_bb)
    {
        return *this;
    }

    m_min = in_bb.m_min;
    m_max = in_bb.m_max;

    return *this;
}

//-------------------------------------------------------------------------
//  friend functions
//-------------------------------------------------------------------------

template<typename Type>
ostream& operator<<(ostream& os, const BoundingBox<Type>& in_bb)
{
    os << "min (" << in_bb.m_min << "), max (" << in_bb.m_max << ")";
    return os;
}

}