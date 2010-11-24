#pragma once

#include "htCommon.h"
#include <cmath>

namespace hooktail
{

    template <typename Type>
    class htVector3
    {
    public:
        htVector3( Type in_x=0, Type in_y=0, Type in_z=0 ) : x(in_x), y(in_y), z(in_z) {}
        htVector3( const Type* in_v ) : x(in_v[0]), x(in_v[1]), x(in_v[2]) {}
        htVector3( const htVector3& in_v ) : x(in_v.x), y(in_v.y), z(in_v.z) {} 

        htVector3&              operator=  ( const htVector3& );

        htVector3&              operator+= ( const htVector3& in_v ) { x+=in_v.x; y+=in_v.y; z+=in_v.z; return *this; }
        htVector3&              operator-= ( const htVector3& in_v ) { x-=in_v.x; y-=in_v.y; z-=in_v.z; return *this; }
        htVector3&              operator*= ( Type in_t ) { x*=in_t; y*=in_t; z*=in_t; return *this; }
        htVector3&              operator/= ( Type t );

        htVector3               operator+  ( const htVector3& v ) const { return htVector3( x+v.x, y+v.y, z+v.z ); }
        htVector3               operator-  ( const htVector3& v ) const { return htVector3( x-v.x, y-v.y, z-v.z ); }
        htVector3               operator*  ( Type t ) const { return htVector3( x*t, y*t, z*t ); }
        htVector3               operator/  ( Type t ) const;

        Type                    operator[] ( int i ) const;
        Type&                   operator[] ( int i );

        Type	                Length() const { return sqrt( sqr( x ) + sqr( y ) + sqr( z )); }
        Type	                LengthSqr() const { return sqr( x ) + sqr( y ) + sqr( z ); }
        void	                Normalize() { *this *= (1.0/Length()); }

        Type*	                Buf() { return (&x); }

        friend htVector3<Type>  operator*(Type t, const htVector3<Type>& v);
        friend Type             Dot(const htVector3<Type>& v0, const htVector3<Type>& v1);
        friend htVector3<Type>  Cross(const htVector3<Type>& v0, const htVector3<Type>& v1);

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
    inline Type htVector3<Type>::operator[] (int i) const
    {
        HT_ASSERT(i >= 0 && i < 3, "Index out-of-bounds in htVector3");
        return m_data[i];
    }

    template <typename Type>
    inline Type& htVector3<Type>::operator[] (int i)
    {
        HT_ASSERT(i >= 0 && i < 3, "Index out-of-bounds in htVector3");
        return m_data[i];
    }

    template <typename Type>
    inline htVector3<Type> htVector3<Type>::operator/ (Type t) const
    {
        HT_ASSERT(t != 0.0, "Divide by zero in htVector3");

        Type inv_t = (Real)1.0/t;

        return htVector3( x*inv_t, y*inv_t, z*inv_t );
    }

    template <typename Type>
    inline htVector3<Type>& htVector3<Type>::operator/= (Type t)
    {
        HT_ASSERT( t != static_cast<Type>0, "Divide by zero in htVector3" );

        Type inv_t = 1.0/t;

        x*=inv_t;
        y*=inv_t;
        z*=inv_t;

        return *this;
    }

    template <typename Type>
    htVector3<Type>& htVector3<Type>::operator= (const htVector3& v)
    {
        if (this == &v)
        {
            return *this;
        }

        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }

    template<typename Type>
    htVector3<Type> operator* (Type t, const htVector3<Type>& v)
    {
        return htVector3<Type>(v.x*t, v.y*t, v.z*t);
    }

    template<typename Type>
    Dot( const htVector3<Type>& v0, const htVector3<Type>& v1)
    {
        return sqrt(v0.x*v1.x + v0.y*v1.y + v0.z*v1.z);
    }

    template<typename Type>
    htVector3<Type>  Cross(const htVector3<Type>& v0, const htVector3<Type>& v1)
    {
        return htVector3<Type>((v0.y*v1.z  - v0.z*v1.y), (v0.z*v1.x - v0.x*v1.z), (v0.x*v1.y - v0.y*v1.x));
    }

} // namespace HOOKTAIL
