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

    Scene(){ }

    ~Scene(){
        for(auto i: _objects)
            delete i;
    }

    template<typename T, typename... Args>
    void add_object(Args&&...args){
        typedef typename std::remove_const<T>::type Tc;
        _objects.push_back(new Tc(std::forward<Args>(args)...));

        if (_light == nullptr){
            Drawable* last = _objects[size() - 1];

            if (last->emit_light())
                _light = last;
        }
    }

    Drawable& operator[] (int i) {  return *_objects[i]; }
    const Drawable& operator[] (int i) const {  return *_objects[i]; }

    // This is scene job
    bool intersect(const Ray& r, double &t, int&id) const {

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

    int size(){ return _objects.size();  }

    // return light position
    Vector3d light() const {    return _light->position(); }

private:
    Drawable* _light{nullptr};
    std::vector<Drawable*> _objects;
};

}

#endif
