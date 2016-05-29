#ifndef RAYTRACING_RENDER_HEADER_
#define RAYTRACING_RENDER_HEADER_

#include <Vector.h>
#include <vector>

#include "ARender.h"
#include "Utils.h"
#include "Debug.h"

namespace raytracing{

class RTRender: public AbstractRender
{
public:
    int bouncing_ray{1000};

    Color specular(Ray r, Vector3d x, Vector3d n, const Drawable& obj, const Scene& scene){
        Color color;

        for (int i = 0; i < bouncing_ray; i++) {
            Vector3d direction = r.dest() - (n * n.dot(r.dest())) * 2;

            Ray ray(x, direction.norm());

            double t  = infinity();
            int    id = 0;
                scene.intersect(ray, t, id);

            const Drawable &obj2 = scene[id];

            //Vector3d newX = ray.o + ray.d * t;
           // Vector3d newN = (newX - obj2.p).norm();

            //Vector3d sirrad;
            //pm.irradiance_estimate(sirrad, newX, newN, DISTANCE, NUM_PHOTONS);

            //DEBUG_VEC(sirrad);

            color = color + obj.color() * obj2.light();
        }

        return color / double(bouncing_ray);
    }

    Color diffuse(Ray r, Vector3d x, Vector3d n, const Drawable& obj, const Scene& scene){
        Color color;

        for (int i = 0; i < bouncing_ray; i++) {
            double theta = acos(sqrt(rand_num(0, 1)));
            double phi   = 2 * M_PI * rand_num(0, 1);

            Vector3d temp;
            if (fabs(n.x()) > 0.1)
                temp = Vector3d(0, 1, 0);
            else
                temp = Vector3d(1, 0, 0);

            Vector3d u = (temp % n).norm();
            Vector3d v = n % u;
            Vector3d w = n;

            Vector3d direction = u * cos(phi) * cos(theta) +
                v * sin(phi) * cos(theta) + w * sin(theta);

            // reflect
            Ray ray(x, direction.norm());

            double t  = infinity();
            int    id = 0;
                scene.intersect(ray, t, id);

            const Drawable &obj2 = scene[id];

            //Vector3d newX = ray.origin() + ray.dest() * t;
            //Vector3d newN = (newX - obj2.position()).norm();

            color = color + obj.color() * obj2.light();
        }
        return color / double(bouncing_ray);
    }

    Color shade(const Scene& scene, const Ray& r){
        int   id = 0;
        double t = 0;

        // Check collision
        if (!scene.intersect(r, t, id))
            return Color(0, 0, 0);

        // retrieve object
        const Drawable& obj = scene[id];

        // Is it a light ?
        if (obj.emit_light())
            return obj.light();

        // Compute correct color
        Vector3d x = r.origin() + r.dest() * t;
        Vector3d n = (x - obj.position()).norm();

        // Compute color in function of material
        switch(obj.material()){
        case Diffuse:
            return diffuse(r, x, n, obj, scene);
        case Specular:
            return specular(r, x, n, obj, scene);
        default:
            DEBUG("UNKNOWN MATERIAL");
            return obj.color() + n;
        }
    }

    void render(const Scene& scene, const Camera& camera, PaintDevice& device){

        // indice / hint : tan(27 / 180.0 * M_PI ) == 0.5095
        int width = device.width();
        int height = device.height();

        Vector3d cx = Vector3d(width * 0.5095 / height, 0., 0.);
        Vector3d cy = (cx % camera.orientation()).norm() * 0.5095;
        Color pix;

        #pragma omp parallel for schedule(dynamic, 1) private(pix)
        for(int y = 0; y < height; ++y) {
            printf("\r%5.2f%%", 100. * y / (height - 1));

            for(int x = 0; x < width; ++x) {

                Vector3d cameraRayDir = cx * (double(x) / width - .5) +
                                        cy * (double(y) / height - .5) + camera.orientation();

                pix = shade(scene, Ray(camera.position(), cameraRayDir.norm()));

                int idx = (height - y - 1) * width + x;
                device[idx] = pix.to_rgb();
             }
        }

        printf("\n");
    }


private:

    std::vector<ColorT<int>> _image;
};
}

#endif
