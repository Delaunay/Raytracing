#ifndef RAYTRACING_SCENE_HEADER_
#define RAYTRACING_SCENE_HEADER_

#include "Drawable.h"
#include "Sphere.h"

#include <vector>
#include <memory>


namespace raytracing{
class Scene
{
public:

    Scene(){
        // default scene
        _objects = {
            new Sphere( 1e5, Vector3d(-1e5 - 49, 0, 0),         Color(.75, .25, .25)),
            new Sphere( 1e5, Vector3d( 1e5 + 49, 0, 0),         Color(.25, .25, .75)),
            new Sphere( 1e5, Vector3d(   0,    0, -1e5 - 81.6), Color(.75, .75, .75)),
            new Sphere( 1e5, Vector3d(   0, -1e5 - 40.8, 0),    Color(.75, .75, .75)),
            new Sphere( 1e5, Vector3d(   0,  1e5 + 40.8, 0),    Color(.75, .75, .75)),

            new Sphere(16.5, Vector3d( -23, -24.3, -34.6),      Color(.999, .999, .999)),
            new Sphere(16.5, Vector3d(  23, -24.3, -3.6),       Color(.999, .999, .999)),
            new Sphere( 8.5, Vector3d(   0,  24.3 , 0),         Color(0.1, 0.1, 0.1),            20)
        };
    }

    ~Scene(){
        for(auto i: _objects)
            delete i;
    }

    Drawable& operator[] (int i) {  return *_objects[i]; }
    const Drawable& operator[] (int i) const {  return *_objects[i]; }

    // This is scene job
    bool intersect(const Ray& r, double &t, int&id){

        t = infinity();

        for(int i = _objects.size() - 1; i >= 0; --i){
            double d = _objects[i]->intersect(r);

            if (d && d < t){
                t = d;
                id = i;
            }
        }

        return t < infinity();
    }

private:

    std::vector<Drawable*> _objects;
};

}

#endif
