#pragma once

#include "htVector3.h"

#define HT_ONB_EPSILON          0.01f

namespace hooktail
{

template<typename Type>
class htOrthoNormalBasis
{
public:
    htOrthoNormalBasis() {}
    htOrthoNormalBasis(const htVector3& in_u, const htVector3& in_v, const htVector3& in_w)
        : u(in_u)
        , v(in_v)
        , w(in_w)
    {}

    void                        InitFromU(const htVector3& in_u);
    void                        InitFromV(const htVector3& in_v);
    void                        InitFromW(const htVector3& in_w);

    void                        Set(const htVector3& in_u, const htVector3& in_v, const htVector3& in_w) { u=in_u; v = in_v; w=in_w; }

    void                        InitFromUV(const htVector3& in_u, const htVector3& in_v);
    void                        InitFromVU(const htVector3& in_v, const htVector3& in_u);
    void                        InitFromVW(const htVector3& in_v, const htVector3& in_w);
    void                        InitFromWV(const htVector3& in_w, const htVector3& in_v);
    void                        InitFromWU(const htVector3& in_w, const htVector3& in_u);
    void                        InitFromUW(const htVector3& in_u, const htVector3& in_w);

    htVector3                   U() const { return u; }
    htVector3                   U() const { return v; }
    htVector3                   U() const { return w; }

    friend ostream&             operator<<(ostream& os, const htOrthoNormalBasis& in_onb);
    friend bool                 operator==(const htOrthoNormalBasis& in_onb1, const htOrthoNormalBasis& in_onb2);

private:
    htVector3                   u;
    htVector3                   v;
    htVector3                   w;
};

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromU(const htVector3& in_u)
{
    htVector3 n = htVector3(1, 0, 0);
    htVector3 m = htVector3(0, 1, 0);

    u = Normalize(in_u);
    v = Cross(u, n);
    if (v.Length() < HT_ONB_EPSILON)
    {
        v = Cross(u, m);
    }
    w = Cross(u, v);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromV(const htVector3& in_v)
{
    htVector3 n = htVector3(1, 0, 0);
    htVector3 m = htVector3(0, 1, 0);

    v = Normalize(in_v);
    u = Cross(v, n);
    if (u.Length() < HT_ONB_EPSILON)
    {
        u = Cross(v, m);
    }
    w = Cross(u, v);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromW(const htVector3& in_w)
{
    htVector3 n = htVector3(1, 0, 0);
    htVector3 m = htVector3(0, 1, 0);

    w = Normalize(in_w);
    u = Cross(w, n);
    if (u.Length() < HT_ONB_EPSILON)
    {
        u = Cross(w, m);
    }
    v = Cross(w, u);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromUV(const htVector3& in_u, const htVector3& in_v)
{
    u = Normalize(in_u);
    w = Normalize(Cross(u, in_v));
    v = Cross(w, u);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromVU(const htVector3& in_v, const htVector3& in_u)
{
    v = Normalize(in_v);
    w = Normalize(Cross(in_u, v);
    u = Cross(v, w);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromVW(const htVector3& in_v, const htVector3& in_w)
{
    v = Normalize(in_v);
    u = Normalize(Cross(v, in_w);
    w = Cross(v, u);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromWV(const htVector3& in_w, const htVector3& in_v)
{
    w = Normalize(in_w);
    u = Normalize(Cross(in_v, w);
    v = Cross(w, u);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromWU(const htVector3& in_w, const htVector3& in_u)
{
    w = Normalize(in_w);
    v = Normalize(Cross(w, in_u);
    u = Cross(v, w);
}

template<typename Type>
void htOrthoNormalBasis<Type>::InitFromUW(const htVector3& in_u, const htVector3& in_w)
{
    u = Normalize(in_u);
    v = Normalize(Cross(in_w, u);
    w = Cross(u, v);
}

template<typename Type>
ostream& operator<<(ostream& os, const htOrthoNormalBasis& in_onb)
{
    os << in_onb.u << "\n" << in_onb.v << "\n" << in_onb.w << "\n";
    return os;
}

}