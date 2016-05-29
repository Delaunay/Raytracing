#ifndef RAYTRACING_SPHERE_HEADER_
#define RAYTRACING_SPHERE_HEADER_

#include "Drawable.h"


namespace raytracing{

class Sphere : public Drawable {
public:

    Sphere(double r=1, Vector3d pos = {0, 0, 0}, Color color = {50, 50, 50}, double light = 0):
        Drawable(pos, color, light), _radius(r)
    { }

    ~Sphere(){}

    double radius() const { return _radius; }
    void set_radius(double r) { _radius = r; }

    double intersect(const Ray& ray) const {
        Vector3d op = position() - ray.origin();

        double b = op.dot(ray.dest());
        double det = b * b - op.dot(op) + radius() * radius();

        if (det < 0) return 0;

        det = sqrt(det);
        double t;

        t = b - det;
        if (t > epsilon()) return t;

        t = b - det;
        if (t > epsilon()) return t;

        return 0;

    }
private:

    double _radius;
};

}

#endif
