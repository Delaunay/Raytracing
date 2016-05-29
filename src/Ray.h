#ifndef RAYTRACING_RAY_HEADER_
#define RAYTRACING_RAY_HEADER_

#include "Vector.h"

namespace raytracing{


class Ray
{
public:
    Ray(Vector3d org, Vector3d dest):
        _origin(org), _dest(dest)
    {}

    Vector3d origin() const  {   return _origin; }
    void set_origin(const Vector3d org) {   _origin = org; }
    void set_origin(double x, double y, double z) {   _origin = Vector3d(x, y, z); }

    Vector3d dest() const    {   return _dest; }
    void set_dest(const Vector3d org) {   _dest = org; }
    void set_dest(double x, double y, double z) {   _dest = Vector3d(x, y, z); }

    double length_sqr() const {   return (dest() - origin()).length_sqr(); }
    double length()     const {   return sqrt(length_sqr()); }

private:
    Vector3d _origin;
    Vector3d _dest;
};

}

#endif
