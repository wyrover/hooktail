#pragma once

#include <iostream>

using std::ostream;

namespace hooktail
{

template<class Type>
class Color
{
public:
                                Color() { r = 0; g = 0; b = 0; }
                                Color(Type in_r, Type in_g, Type in_b) : r(in_r), g(in_g), b(in_b) {}
                                Color(const Color &in_rgb) { *this = in_rgb; }

    void                        SetR(const Type in_r) { r = in_r; }
    void                        SetG(const Type in_g) { g = in_g; }
    void                        SetB(const Type in_b) { b = in_b; }

    Type                        R() const { return r; }
    Type                        G() const { return g; }
    Type                        B() const { return b; }

    Color&                      operator=(const Color &in_rhs);
    Color&                      operator+=(const Color &in_rhs);
    Color&                      operator*=(const Color &in_rhs);
    Color&                      operator/=(const Color &in_rhs);
    Color&                      operator*=(Type in_rhs);
    Color&                      operator/=(Type in_rhs);

    friend ostream&             operator<<(ostream &out_str, const Color &in_rgb);
    friend Color                operator*(const Color &in_rgb, Type in_val);
    friend Color                operator*(Type in_val, const Color& in_rgb);
    friend Color                operator/(const Color& in_rgb, Type in_val);
    friend Color                operator*(const Color& in_rgbl, const Color& in_rgb2);
    friend Color                operator/(const Color& in_rgb1, const Color& in_rgb2);
    friend Color                operator+(const Color& in_rgb1, const Color& in_rgb2);

private:
    union
    {
        struct 
        {
            Type r;
            Type g;
            Type b;
        };
        Type m_values[3];
    };
};

template<class Type>
HT_INLINE Color<Type>&
Color<Type>::operator=(const Color &in_rhs)
{
    r = in_rhs.r;
    g = in_rhs.g;
    b = in_rhs.b;
    return *this;
}

template<class Type>
HT_INLINE Color<Type>&
Color<Type>::operator+=(const Color<Type> &in_rhs)
{
    *this = *this + in_rhs;
    return *this;
}

template<class Type>
HT_INLINE Color<Type>&
Color<Type>::operator*=(const Color<Type> &in_rhs)
{
    *this = *this * in_rhs;
    return *this;
}

template<class Type>
HT_INLINE Color<Type>&
Color<Type>::operator/=(const Color<Type> &in_rhs)
{
    *this = *this / in_rhs;
    return *this;
}

template<class Type>
HT_INLINE Color<Type>&
Color<Type>::operator*=(Type in_rhs)
{
    *this = *this * in_rhs;
    return *this;
}

template<class Type>
HT_INLINE Color<Type>&
Color<Type>::operator/=(Type in_rhs)
{
    *this = *this / in_rhs;
    return *this;
}

template<class Type>
HT_INLINE ostream&
operator<<(ostream &out_str, const Color<Type> &in_rgb)
{
    out_str << "(" << in_rgb.r << ", " << in_rgb.g << ", " << in_rgb.b << ")";
    return out_str;
}

template<class Type>
HT_INLINE Color<Type>
operator*(const Color<Type> &in_rgb, Type in_val)
{
    return Color<Type>(in_rgb.r*in_val.r, in_rgb.g*in_val.g, in_rgb.b*in_val.b);
}

template<class Type>
HT_INLINE Color<Type>
operator*(Type in_val, const Color<Type>& in_rgb)
{
    return Color<Type>(in_rgb.r*in_val.r, in_rgb.g*in_val.g, in_rgb.b*in_val.b);
}

template<class Type>
HT_INLINE Color<Type>
operator/(const Color<Type>& in_rgb, Type in_val)
{
    HT_ASSERT(in_val != Type(0));
    return Color<Type>(in_rgb.r*in_val.r, in_rgb.g*in_val.g, in_rgb.b*in_val.b);
}

template<class Type>
HT_INLINE Color<Type>
operator*(const Color<Type>& in_rgbl, const Color<Type>& in_rgb2)
{
    return Color<Type>(in_rgbl.r*in_rgb2.r, in_rgbl.g*in_rgb2.g, in_rgbl.b*in_rgb2.b);
}

template<class Type>
HT_INLINE Color<Type>
operator/(const Color<Type>& in_rgb1, const Color<Type>& in_rgb2)
{
    HT_ASSERT((in_rgb2.r != Type(0)) || (in_rgb2.g != Type(0)) || (in_rgb2.b != Type(0)));
    return Color<Type>(in_rgbl.r*in_rgb2.r, in_rgbl.g*in_rgb2.g, in_rgbl.b*in_rgb2.b);
}

template<class Type>
HT_INLINE Color<Type>
operator+(const Color<Type>& in_rgb1, const Color<Type>& in_rgb2)
{
    return Color<Type>(in_rgbl.r+in_rgb2.r, in_rgbl.g+in_rgb2.g, in_rgbl.b+in_rgb2.b);
}

} // namespace hooktail