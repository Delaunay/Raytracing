#ifndef RAYTRACING_RENDER_HEADER_
#define RAYTRACING_RENDER_HEADER_

#include <Vector.h>
#include <vector>

#include "ARender.h"

namespace raytracing{

class RTRender: public AbstractRender
{
public:

    Color shade(const Scene& scene, const Ray& r){
        int id = 0;
        double t = 0;

        // Check collision
        if (!scene.intersect(r, t, id))
            return Color(0, 0, 0);

        // retrieve object
        const Drawable& obj = scene[id];
        Vector3d x = r.origin() + r.dest() * t;
        Vector3d n = (x - obj.position()).norm();

        return obj.color() + n;
    }

    void render(const Scene& scene, const Camera& camera, PaintDevice& device){

        // indice / hint : tan(27 / 180.0 * M_PI ) == 0.5095
        int width = device.width();
        int height = device.height();

        Vector3d cx = Vector3d(width * 0.5095 / height, 0., 0.);
        Vector3d cy = (cx % camera.orientation()).norm() * 0.5095;

        #pragma omp parallel for schedule(dynamic, 1) private(pix)
        for(int y = 0; y < height; ++y) {
             for(int x = 0; x < width; ++x) {

                Vector3d cameraRayDir = cx * (double(x) / width - .5) +
                                        cy * (double(y) / height - .5) + camera.orientation();

                Color pix = shade(scene, Ray(camera.position(), cameraRayDir.norm()));

                int idx = (height - y - 1) * width + x;
                device[idx] = pix.to_rgb();
             }
        }
    }


private:

    std::vector<ColorT<int>> _image;
};
}

#endif
