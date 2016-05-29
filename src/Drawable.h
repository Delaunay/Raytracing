#ifndef RAYTRACING_DRAWABLE_HEADER_
#define RAYTRACING_DRAWABLE_HEADER_

#include "Color.h"
#include "Vector.h"
#include "Ray.h"


double epsilon(){
    static const double eps = 1e-6;
    return eps;
}

double infinity(){
    static const double eps = 1e20;
    return eps;
}

namespace raytracing{

enum Material{
    Diffuse,
    Specular,
};

/**
 *  Drawable object. This is the base class used to define new
 *  object to be rendered
 */
class Drawable{
public:

    Drawable(Vector3d pos = {0, 0, 0}, Color color = {0.5, 0.5, 0.5}, Color light = {0, 0, 0}, Material m = Diffuse):
        _position(pos), _color(color), _light(light), _material(m)
    {}

    ~Drawable(){}

    // Intersection
    virtual double intersect(const Ray& ray) const = 0;

    Vector3d position() const {   return _position; }
    void set_position(const Vector3d pos) { _position = pos; }
    void set_position(double x, double y, double z) { _position = Vector3d(x, y, z); }

    Color color() const  {   return _color; }
    void set_color(const Color pos) { _color = pos; }
    void set_color(double x, double y, double z) { _color = Color(x, y, z); }

    Color light() const { return _light; }
    bool emit_light() const  { return _light.any(); }
    void set_emit_light(Color intensity){  _light = intensity; }

    Material material() const { return _material; }
    void set_material(Material m) { _material = m;  }

private:
    Vector3d _position;
    Color    _color;
    Color    _light;
    Material _material;
};

}

#endif
