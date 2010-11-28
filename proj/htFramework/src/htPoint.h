#pragma once

#include "htCommon.h"
#include "htVector3.h"
#include <cmath>
#include <iostream>

namespace hooktail
{

template<typename Type>
class Point
{
public:
    Point( Type in_x=0, Type in_y=0, Type in_z=0 ) : x(in_x), y(in_y), z(in_z) {}
    Point( const Type* in_p ) : x(in_p[0]), x(in_p[1]), x(in_p[2]) {}
    Point( const Point& in_p ) : x(in_p.x), y(in_p.y), z(in_p.z) {} 
    Point( const Vector3<Type>& in_v ) : x(in_v.x), y(in_v.y), z(in_v.z) {} 

    Point&                      operator=  ( const Point& );

    Point&                      operator+= ( const Vector3& in_v ) { x+=in_v.x; y+=in_v.y; z+=in_v.z; return *this; }
    Point&                      operator-= ( const Vector3& in_v ) { x-=in_v.x; y-=in_v.y; z-=in_v.z; return *this; }
    Point&                      operator*= ( Type in_t ) { x*=in_t; y*=in_t; z*=in_t; return *this; }
    Point&                      operator/= ( Type t );

    Point                       operator+  ( const Vector3<Type>& in_v ) const { return Point( x+in_v.x, y+in_v.y, z+in_v.z ); }
    Point                       operator-  ( const Vector3<Type>& in_v ) const { return Point( x-in_v.x, y-in_v.y, z-in_v.z ); }
    Vector3<Type>               operator+  ( const Point& in_p ) const { return Vector3<Type>( x+in_p.x, y+in_p.y, z+in_p.z ); }
    Vector3<Type>               operator-  ( const Point& in_p ) const { return Vector3<Type>( x-in_p.x, y-in_p.y, z-in_p.z ); }
    Point                       operator*  ( Type t ) const { return Point( x*t, y*t, z*t ); }
    Point                       operator/  ( Type t ) const;

    Type                        operator[] ( int i ) const;
    Type&                       operator[] ( int i );
                            
    void                        SetX(const Type in_x) { x = in_x; }
    void                        SetY(const Type in_y) { y = in_y; }
    void                        SetZ(const Type in_z) { z = in_z; }
                                
    Type                        X() const { return x; }
    Type                        Y() const { return y; }
    Type                        Z() const { return z; }

    Type                        GetMinComponent() const;
    Type                        GetMaxComponent() const;
    Type                        GetMinAbsComponent() const;
    Type                        GetMaxAbsComponent() const;

    int                         IndexOfMinComponent() const;
    int                         IndexOfMaxComponent() const;
    int                         IndexOfMinAbsComponent() const;
    int                         IndexOfMaxAbsComponent() const;

    Type*	                    Buf() { return (&x); }

    friend Point                operator*(Type t, const Point& in_p);
    friend ostream&             operator<<(ostream& os, const Point& in_p);
    friend Type                 Dist(const Point& p1, const Point& p2);
    friend Type                 DistSqr(const Point& p1, const Point& p2);

private:
    union
    {
        struct
        {
            Type x;
            Type y;
            Type z;
        };
        Type m_data[3];
    };
};


template <typename Type>
HT_INLINE Type Point<Type>::operator[] (int i) const
{
    HT_ASSERT_STR(i >= 0 && i < 3, "Index out-of-bounds in Point");
    return m_data[i];
}

template <typename Type>
HT_INLINE Type& Point<Type>::operator[] (int i)
{
    HT_ASSERT_STR(i >= 0 && i < 3, "Index out-of-bounds in Point");
    return m_data[i];
}

template <typename Type>
HT_INLINE Point<Type> Point<Type>::operator/ (Type t) const
{
    HT_ASSERT_STR(t != 0.0, "Divide by zero in Point");

    Type inv_t = (Type)1.0/t;

    return Point( x*inv_t, y*inv_t, z*inv_t );
}

template <typename Type>
HT_INLINE Point<Type>& Point<Type>::operator/= (Type t)
{
    HT_ASSERT_STR( t != static_cast<Type>0, "Divide by zero in Point" );

    Type inv_t = 1.0/t;

    x*=inv_t;
    y*=inv_t;
    z*=inv_t;

    return *this;
}

template <typename Type>
HT_INLINE Point<Type>& Point<Type>::operator= (const Point& in_p)
{
    if (this == &in_p)
    {
        return *this;
    }

    x = in_p.x;
    y = in_p.y;
    z = in_p.z;

    return *this;
}

template <typename Type>
HT_INLINE Type Point<Type>::GetMinComponent() const
{
    return min(x, min(y, z));
}

template <typename Type>
HT_INLINE Type Point<Type>::GetMaxComponent() const
{
    return max(x, max(y, z));
}

template <typename Type>
HT_INLINE Type Point<Type>::GetMinAbsComponent() const
{
    return min(abs(x), min(abs(y), abs(z)));
}

template <typename Type>
HT_INLINE Type Point<Type>::GetMaxAbsComponent() const
{
    return max(abs(x), max(abs(y), abs(z)));
}

template <typename Type>
HT_INLINE int Point<Type>::IndexOfMinComponent() const
{
    int idx=0;

    for (int i=1; i<ARRAY_SIZE(m_data); ++i)
    {
        if ( m_data[i] < m_data[idx])
        {
            idx = i;
        }
    }

    return i;
}

template <typename Type>
HT_INLINE int Point<Type>::IndexOfMaxComponent() const
{
    int idx=0;

    for (int i=1; i<ARRAY_SIZE(m_data); ++i)
    {
        if ( m_data[i] > m_data[idx])
        {
            idx = i;
        }
    }

    return i;
}

template <typename Type>
HT_INLINE int Point<Type>::IndexOfMinAbsComponent() const
{
    int idx=0;

    for (int i=1; i<ARRAY_SIZE(m_data); ++i)
    {
        if ( abs(m_data[i]) < abs(m_data[idx]))
        {
            idx = i;
        }
    }

    return i;
}

template <typename Type>
HT_INLINE int Point<Type>::IndexOfMaxAbsComponent() const
{
    int idx=0;

    for (int i=1; i<ARRAY_SIZE(m_data); ++i)
    {
        if ( abs(m_data[i]) > abs(m_data[idx]))
        {
            idx = i;
        }
    }

    return i;
}



//-------------------------------------------------------------------------
//  friend functions
//-------------------------------------------------------------------------

template<typename Type>
HT_INLINE Point<Type> operator*(Type t, const Point<Type>& in_p)
{
    return Point<Type>(in_p.x*t, in_p.y*t, in_p.z*t);
}

template<typename Type>
HT_INLINE ostream& operator<<(ostream& os, const Point<Type>& in_p)
{
    os << in_p[0] << " " << in_p[1] << " " << in_p[2];
    return os;
}

template<typename Type>
HT_INLINE Type Dist(const Point<Type>& p1, const Point<Type>& p2)
{
    return sqrt( DistSqr(p1, p2));
}

template<typename Type>
HT_INLINE Type DistSqr(const Point<Type>& p1, const Point<Type>& p2)
{
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}


}