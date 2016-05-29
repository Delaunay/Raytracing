#ifndef RAYTRACING_VECTOR_HEADER_
#define RAYTRACING_VECTOR_HEADER_

#include <cmath>

namespace raytracing{

template<typename T>
class Vector3
{
public:

    Vector3(T x = 0, T y = 0, T z = 0)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
    }

    // element wise operator
    Vector3 operator+(const Vector3 b) const {  return Vector3(x() + b.x(), y() + b.y(), z() + b.z()); }
    Vector3 operator-(const Vector3 b) const {  return Vector3(x() - b.x(), y() - b.y(), z() - b.z()); }
    Vector3 operator*(const Vector3 b) const {  return Vector3(x() * b.x(), y() * b.y(), z() * b.z()); }

    // constant
    Vector3 operator+(const T b) const {  return Vector3(x() + b, y() + b, z() + b); }
    Vector3 operator-(const T b) const {  return Vector3(x() - b, y() - b, z() - b); }
    Vector3 operator*(const T b) const {  return Vector3(x() * b, y() * b, z() * b); }
    Vector3 operator/(const T b) const {  return Vector3(x() / b, y() / b, z() / b); }

    Vector3 operator%(const Vector3 b) const {
        return Vector3(y() * b.z() - z() * b.y(),
                       z() * b.x() - x() * b.z(),
                       x() * b.y() - y() * b.x());
    }

    double dot(const Vector3 &b) const {
        return x() * b.x() + y() * b.y() + z() * b.z();
    }

    double length_sqr() {   return x() * x() + y() * y() + z() * z(); }
    double length()     {   return sqrt(length_sqr()); }

    Vector3& norm(){
        *this = *this / length();
        return *this;
    }

    // accessor
    T& x() {    return _data[0]; }
    T& y() {    return _data[1]; }
    T& z() {    return _data[2]; }

    T& operator[] (int idx) {   return _data[idx]; }

    // const accessor
    T x() const {    return _data[0]; }
    T y() const {    return _data[1]; }
    T z() const {    return _data[2]; }

    T operator[] (int idx) const {   return _data[idx]; }

private:
    T _data[3];
};

typedef Vector3<float>  Vector3f;
typedef Vector3<double> Vector3d;

}

#endif
