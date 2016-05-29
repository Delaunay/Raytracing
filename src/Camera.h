#ifndef RAYTRACING_CAMERA_HEADER_
#define RAYTRACING_CAMERA_HEADER_

#include "Ray.h"

namespace raytracing
{

class Camera : public Ray
{
public:
    Camera(Vector3d org, Vector3d dest):
        Ray(org, dest)
    {}

    Vector3d position() const  {   return origin(); }
    void set_position(const Vector3d org) {   set_origin(org); }
    void set_position(double x, double y, double z) {   set_origin(x, y, z); }

    Vector3d orientation() const    {   return dest(); }
    void set_orientation(const Vector3d org) {   set_dest(org); }
    void set_orientation(double x, double y, double z) {   set_dest(x, y, z); }

};

}

#endif
