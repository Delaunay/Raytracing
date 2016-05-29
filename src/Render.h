#ifndef RAYTRACING_RENDER_HEADER_
#define RAYTRACING_RENDER_HEADER_

#include <Vector.h>
#include <vector>

#include "Camera.h"
#include "Scene.h"

namespace raytracing{

class Render
{
public:
    typedef std::vector<ColorT<int>> Image;

    Render(int w=1024, int h=768):
        _width(w), _height(h), _camera(Vector3d(0, 11.2, 214),
                                       Vector3d(0, -0.042612, -1).norm())
    { }

    Color shade(const Ray& r){
        int id = 0;
        double t = 0;

        // Check collision
        if (!_scene.intersect(r, t, id))
            return Color(0, 0, 0);

        // retrieve object
        const Drawable& obj = _scene[id];
        Vector3d x = r.origin() + r.dest() * t;
        Vector3d n = (x - obj.position()).norm();

        return obj.color() + n;
    }

    void render(){

        // indice / hint : tan(27 / 180.0 * M_PI ) == 0.5095
        _image = Image(size());

        Vector3d cx = Vector3d(_width * 0.5095 / _height, 0., 0.);
        Vector3d cy = (cx % _camera.orientation()).norm() * 0.5095;

        #pragma omp parallel for schedule(dynamic, 1) private(pixelValue)
        for(int y = 0; y < _height; ++y) {
             for(int x = 0; x < _width; ++x) {

                Vector3d cameraRayDir = cx * (double(x) / _width - .5) +
                                        cy * (double(y) / _height - .5) + _camera.orientation();

                Color pix = shade(Ray(_camera.position(), cameraRayDir.norm()));

                int idx = (_height - y - 1) * _width + x;
                _image[idx] = pix.to_rgb();
             }
        }
    }

    void to_image(){

        FILE *f = fopen("image.ppm", "w");

        fprintf(f, "P3\n%d %d\n%d\n", _width, _height, 255);

        for (int p = 0; p < size(); ++p) {
            fprintf(f, "%d %d %d ", _image[p].x(), _image[p].y(), _image[p].z());
        }

        fclose(f);
    }

    int size() {    return _width * _height; }


private:
    int _width;
    int _height;

    std::vector<ColorT<int>> _image;

    Scene   _scene;
    Camera  _camera;
};
}

#endif
