#ifndef RAYTRACING_COLOR_HEADER_
#define RAYTRACING_COLOR_HEADER_

#include "Vector.h"

namespace raytracing{

template<typename T>
class ColorT: public Vector3<T>
{
public:

    ColorT(T x = 0, T y = 0, T z = 0):
        Vector3<T>(x, y, z)
    {}

    // element wise operator
    ColorT operator+(const Vector3<T> v) const {  return ColorT(r() + v.x(), g() + v.y(), b() + v.z()); }
    ColorT operator-(const Vector3<T> v) const {  return ColorT(r() - v.x(), g() - v.y(), b() + v.z()); }
    ColorT operator*(const Vector3<T> v) const {  return ColorT(r() * v.x(), g() * v.y(), b() * v.z()); }

    static double clamp(double x)  { return x > 1 ? 1 : x < 0 ? 0 : x; }
    static int to_rgb(double x) { return int(pow(clamp(x), 1.0 / 2.2) * 255 + .5);}

    // color must be between 0 and 1
    ColorT clamp(){ return ColorT(clamp(r()), clamp(g()), clamp(b()));  }

    // color must be between 0 and 255
    ColorT<int> to_rgb(){ return ColorT<int>(to_rgb(r()), to_rgb(g()), to_rgb(b()));  }

    // accessor
    T& r() {    return (*this)[0]; }
    T& g() {    return (*this)[1]; }
    T& b() {    return (*this)[2]; }

    // const accessor
    T r() const {    return (*this)[0]; }
    T g() const {    return (*this)[1]; }
    T b() const {    return (*this)[2]; }
};


typedef ColorT<double> Color;
}

#endif
