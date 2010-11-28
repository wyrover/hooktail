#pragma once

#include "htCommon.h"
#include <cmath>
#include <iostream>

using std::ostream;

namespace hooktail
{

    template <typename Type>
    class Vector3
    {
    public:
        Vector3( Type in_x=0, Type in_y=0, Type in_z=0 ) : x(in_x), y(in_y), z(in_z) {}
        Vector3( const Type* in_v ) : x(in_v[0]), x(in_v[1]), x(in_v[2]) {}
        Vector3( const Vector3& in_v ) : x(in_v.x), y(in_v.y), z(in_v.z) {} 
                           
        Vector3&                operator=  ( const Vector3& );
                           
        Vector3&                operator+= ( const Vector3& in_v ) { x+=in_v.x; y+=in_v.y; z+=in_v.z; return *this; }
        Vector3&                operator-= ( const Vector3& in_v ) { x-=in_v.x; y-=in_v.y; z-=in_v.z; return *this; }
        Vector3&                operator*= ( Type in_t ) { x*=in_t; y*=in_t; z*=in_t; return *this; }
        Vector3&                operator/= ( Type t );
                           
        Vector3                 operator+  ( const Vector3& v ) const { return Vector3( x+v.x, y+v.y, z+v.z ); }
        Vector3                 operator-  ( const Vector3& v ) const { return Vector3( x-v.x, y-v.y, z-v.z ); }
        Vector3                 operator*  ( Type t ) const { return Vector3( x*t, y*t, z*t ); }
        Vector3                 operator/  ( Type t ) const;

        Type                    operator[] ( int i ) const;
        Type&                   operator[] ( int i );

        void                    SetX(const Type in_x) { x = in_x; }
        void                    SetY(const Type in_y) { y = in_y; }
        void                    SetZ(const Type in_z) { z = in_z; }

        Type	                Length() const { return sqrt( sqr( x ) + sqr( y ) + sqr( z )); }
        Type	                LengthSqr() const { return sqr( x ) + sqr( y ) + sqr( z ); }
        void	                Normalize() { *this *= (1.0/Length()); }

        Type                    GetMinComponent() const;
        Type                    GetMaxComponent() const;
        Type                    GetMinAbsComponent() const;
        Type                    GetMaxAbsComponent() const;

        int                     IndexOfMinComponent() const;
        int                     IndexOfMaxComponent() const;
        int                     IndexOfMinAbsComponent() const;
        int                     IndexOfMaxAbsComponent() const;

        Type*	                Buf() { return (&x); }

        friend Vector3          operator*(Type t, const Vector3& in_v);

        friend Type             Dot(const Vector3& v0, const Vector3& v1);
        friend Vector3          Cross(const Vector3& v0, const Vector3& v1);
        friend Vector3          Normalize(const Vector3& in_v);
        friend ostream&         operator<<(ostream& os, const Vector3& in_v);

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
    HT_INLINE Type Vector3<Type>::operator[] (int i) const
    {
        HT_ASSERT_STR(i >= 0 && i < 3, "Index out-of-bounds in Vector3");
        return m_data[i];
    }

    template <typename Type>
    HT_INLINE Type& Vector3<Type>::operator[] (int i)
    {
        HT_ASSERT_STR(i >= 0 && i < 3, "Index out-of-bounds in Vector3");
        return m_data[i];
    }

    template <typename Type>
    HT_INLINE Vector3<Type> Vector3<Type>::operator/ (Type t) const
    {
        HT_ASSERT_STR(t != 0.0, "Divide by zero in Vector3");

        Type inv_t = (Type)1.0/t;

        return Vector3( x*inv_t, y*inv_t, z*inv_t );
    }

    template <typename Type>
    HT_INLINE Vector3<Type>& Vector3<Type>::operator/= (Type t)
    {
        HT_ASSERT_STR( t != static_cast<Type>0, "Divide by zero in Vector3" );

        Type inv_t = 1.0/t;

        x*=inv_t;
        y*=inv_t;
        z*=inv_t;

        return *this;
    }

    template <typename Type>
    HT_INLINE Vector3<Type>& Vector3<Type>::operator= (const Vector3& v)
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

    template <typename Type>
    HT_INLINE Type Vector3<Type>::GetMinComponent() const
    {
        return min(x, min(y, z));
    }

    template <typename Type>
    HT_INLINE Type Vector3<Type>::GetMaxComponent() const
    {
        return max(x, max(y, z));
    }

    template <typename Type>
    HT_INLINE Type Vector3<Type>::GetMinAbsComponent() const
    {
        return min(abs(x), min(abs(y), abs(z)));
    }

    template <typename Type>
    HT_INLINE Type Vector3<Type>::GetMaxAbsComponent() const
    {
        return max(abs(x), max(abs(y), abs(z)));
    }

    template <typename Type>
    HT_INLINE int Vector3<Type>::IndexOfMinComponent() const
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
    HT_INLINE int Vector3<Type>::IndexOfMaxComponent() const
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
    HT_INLINE int Vector3<Type>::IndexOfMinAbsComponent() const
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
    HT_INLINE int Vector3<Type>::IndexOfMaxAbsComponent() const
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
    HT_INLINE Vector3<Type> operator* (Type t, const Vector3<Type>& in_v)
    {
        return Vector3<Type>(in_v.x*t, in_v.y*t, in_v.z*t);
    }

    template<typename Type>
    HT_INLINE Vector3<Type> Dot( const Vector3<Type>& v0, const Vector3<Type>& v1)
    {
        return sqrt(v0.x*v1.x + v0.y*v1.y + v0.z*v1.z);
    }

    template<typename Type>
    HT_INLINE Vector3<Type> Cross(const Vector3<Type>& v0, const Vector3<Type>& v1)
    {
        return Vector3<Type>((v0.y*v1.z  - v0.z*v1.y), (v0.z*v1.x - v0.x*v1.z), (v0.x*v1.y - v0.y*v1.x));
    }

    template<typename Type>
    HT_INLINE Vector3<Type> Normalize(const Vector3<Type>& in_v)
    {
        Vector3<Type>   vec = in_v;
        return in_v.Normalize();
    }

    template< typename Type >
    HT_INLINE ostream& operator<<( ostream& os, const Vector3<Type>& in_v )
    {
        os << in_v[0] << " " << in_v[1] << " " << in_v[2];
        return os;
    }

} // namespace HOOKTAIL
