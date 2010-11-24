#pragma once

#include <iostream>

using std::ostream;

namespace hooktail
{

template<class T>
class htRGB
{
public:
                                htRGB() { r = 0; g = 0; b = 0; }
                                htRGB(T in_r, T in_g, T in_b) : r(in_r), g(in_g), b(in_b) {}
                                htRGB(const htRGB &in_rgb) { *this = in_rgb; }

    void                        SetR(const T in_r) { r = in_r; }
    void                        SetG(const T in_g) { g = in_g; }
    void                        SetB(const T in_b) { b = in_b; }

    T                           R() const { return r; }
    T                           G() const { return g; }
    T                           B() const { return b; }

    htRGB&                      operator=(const htRGB &in_rhs);
    htRGB&                      operator+=(const htRGB &in_rhs);
    htRGB&                      operator*=(const htRGB &in_rhs);
    htRGB&                      operator/=(const htRGB &in_rhs);
    htRGB&                      operator*=(T in_rhs);
    htRGB&                      operator/=(T in_rhs);

    friend ostream&             operator<<(ostream &out_str, const htRGB &in_rgb);
    friend htRGB                operator*(const htRGB &in_rgb, T in_val);
    friend htRGB                operator*(T in_val, const htRGB& in_rgb);
    friend htRGB                operator/(const htRGB& in_rgb, T in_val);
    friend htRGB                operator*(const htRGB& in_rgbl, const htRGB& in_rgb2);
    friend htRGB                operator/(const htRGB& in_rgb1, const htRGB& in_rgb2);
    friend htRGB                operator+(const htRGB& in_rgb1, const htRGB& in_rgb2);

private:
    union
    {
        T r, g, b;
        //T m_values[3];
    };
};

template<class T>
inline htRGB<T>&
htRGB<T>::operator=(const htRGB &in_rhs)
{
    r = in_rhs.r;
    g = in_rhs.g;
    b = in_rhs.b;
    return *this;
}

template<class T>
inline htRGB<T>&
htRGB<T>::operator+=(const htRGB<T> &in_rhs)
{
    *this = *this + in_rhs;
    return *this;
}

template<class T>
inline htRGB<T>&
htRGB<T>::operator*=(const htRGB<T> &in_rhs)
{
    *this = *this * in_rhs;
    return *this;
}

template<class T>
inline htRGB<T>&
htRGB<T>::operator/=(const htRGB<T> &in_rhs)
{
    *this = *this / in_rhs;
    return *this;
}

template<class T>
inline htRGB<T>&
htRGB<T>::operator*=(T in_rhs)
{
    *this = *this * in_rhs;
    return *this;
}

template<class T>
inline htRGB<T>&
htRGB<T>::operator/=(T in_rhs)
{
    *this = *this / in_rhs;
    return *this;
}

template<class T>
inline ostream&
operator<<(ostream &out_str, const htRGB<T> &in_rgb)
{
    out_str << "(" << in_rgb.r << ", " << in_rgb.g << ", " << in_rgb.b << ")";
    return out_str;
}

template<class T>
inline htRGB<T>
operator*(const htRGB<T> &in_rgb, T in_val)
{
    return htRGB<T>(in_rgb.r*in_val.r, in_rgb.g*in_val.g, in_rgb.b*in_val.b);
}

template<class T>
inline htRGB<T>
operator*(T in_val, const htRGB<T>& in_rgb)
{
    return htRGB<T>(in_rgb.r*in_val.r, in_rgb.g*in_val.g, in_rgb.b*in_val.b);
}

template<class T>
inline htRGB<T>
operator/(const htRGB<T>& in_rgb, T in_val)
{
    HT_ASSERT(in_val != T(0));
    return htRGB<T>(in_rgb.r*in_val.r, in_rgb.g*in_val.g, in_rgb.b*in_val.b);
}

template<class T>
inline htRGB<T>
operator*(const htRGB<T>& in_rgbl, const htRGB<T>& in_rgb2)
{
    return htRGB<T>(in_rgbl.r*in_rgb2.r, in_rgbl.g*in_rgb2.g, in_rgbl.b*in_rgb2.b);
}

template<class T>
inline htRGB<T>
operator/(const htRGB<T>& in_rgb1, const htRGB<T>& in_rgb2)
{
    HT_ASSERT((in_rgb2.r != T(0)) || (in_rgb2.g != T(0)) || (in_rgb2.b != T(0)));
    return htRGB<T>(in_rgbl.r*in_rgb2.r, in_rgbl.g*in_rgb2.g, in_rgbl.b*in_rgb2.b);
}

template<class T>
inline htRGB<T>
operator+(const htRGB<T>& in_rgb1, const htRGB<T>& in_rgb2)
{
    return htRGB<T>(in_rgbl.r+in_rgb2.r, in_rgbl.g+in_rgb2.g, in_rgbl.b+in_rgb2.b);
}

} // namespace hooktail