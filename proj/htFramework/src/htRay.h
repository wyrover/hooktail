#pragma once

#include "htCommon.h"
#include "htVector3.h"
#include "htPoint.h"

#include <iostream>

using std::ostream;

namespace hooktail
{

template<typename Type>
class Ray
{
public:
    Ray() {}
    Ray(Point<Type>& in_orig, Vector3<Type> in_dir) : m_orig(in_orig), m_dir(in_dir) {}
    Ray(const Ray<Type>& in_ray) : m_orig(in_ray.m_orig), m_dir(in_ray.m_dir) {}

    Ray&                        operator=(const Ray& in_ray);

    void                        SetOrigin(Point<Type>& in_p) { m_orig(in_p); }
    void                        SetDirection(Vector3<Type>& in_v) { m_dir(in_v); }

    Point<Type>                 GetOrigin() const { return m_orig; }
    Vector3<Type>               GetDirection() const { return m_dir; }

    Point<Type>                 PointOnRay(Type v) const { return Point<Type>(m_orig + v*m_dir); }

    friend ostream&             operator<<(ostream& os, const Ray& in_ray);
    
private:
    Point<Type>                 m_orig;
    Vector3<Type>               m_dir;
};

template<typename Type>
HT_INLINE Ray<Type>& Ray<Type>::operator=(const Ray& in_ray)
{
    if(this == &in_ray)
    {
        return *this;
    }

    m_orig = in_ray.m_orig;
    m_dir = in_ray.m_dir;

    return *this;
}

