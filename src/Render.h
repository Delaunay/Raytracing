#ifndef RAYTRACING_RENDER_HEADER_
#define RAYTRACING_RENDER_HEADER_

#include <Vector.h>
#include <vector>

#include "ARender.h"
#include "Utils.h"
#include "Debug.h"

#define PHOTON_MAPPING 1

#if PHOTON_MAPPING
#   include "../dependencies/PhotonMap.h"
#endif

namespace raytracing{

class RTRender: public AbstractRender
{
public:

    Color specular(Ray r, Vector3d x, Vector3d n, const Drawable& obj, const Scene& scene){
        Color color;

        for (int i = 0; i < bouncing_ray; i++) {
            Vector3d direction = r.dest() - (n * n.dot(r.dest())) * 2;

            Ray ray(x, direction.norm());

            double t  = infinity();
            int    id = 0;
                scene.intersect(ray, t, id);

            const Drawable &obj2 = scene[id];

        #if PHOTON_MAPPING
            Vector3d newX = ray.origin() + ray.dest() * t;
            Vector3d newN = (newX - obj2.position()).norm();

            Vector3d sirrad;
            photon_map.irradiance_estimate(sirrad, newX, newN, distance, num_photons);

            color = color + sirrad * obj2.color() + obj2.color() * obj2.color();
        #else
            color = color + obj2.color() * obj2.color();
        #endif
        }

        return color / double(bouncing_ray);
    }

    Color diffuse(Ray, Vector3d x, Vector3d n, const Drawable& obj, const Scene& scene){
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

        #if PHOTON_MAPPING
            Vector3d newX = ray.origin() + ray.dest() * t;
            Vector3d newN = (newX - obj2.position()).norm();

            Vector3d irrad;
            photon_map.irradiance_estimate(irrad, newX, newN, distance, num_photons);

            color = color + obj.color() * obj2.light() + irrad * obj.color();
        #else
            color = color + obj.color() * obj2.light();
        #endif
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
    #if PHOTON_MAPPING
        emit_photons(scene);
    #endif
        int width = device.width();
        int height = device.height();

        // FIXME: Hardcoded value
        // indice / hint : tan(27 / 180.0 * M_PI ) == 0.5095
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

    int bouncing_ray{100};

#if PHOTON_MAPPING

    double distance{0.5};
    int num_photons{500000};
    int max_reflect{5};

    // probabitility of reflection
    float pDiffuse  = 0.5;
    float pSpecular = 0.5;

    PhotonMap photon_map{num_photons * max_reflect};
#   define MAX_PHOTONS num_photons * max_reflect

    void emit_photons(const Scene& scene){
        float x = 0, y = 0, z = 0;
        Vector3d power(1.0, 1.0, 1.0);

        for (int i = 0; i < num_photons; ++i) {
            // Generate Origin offset
            x = 0.1 * rand_num(-1, 1);
            z = 0.1 * rand_num(-1, 1);

            Vector3d offset = scene.light() + Vector3d(x, y, z);

            // Generate Direction
            do {
                x = rand_num(-1, 1);
                y = rand_num(-1, 0);
                z = rand_num(-1, 1);
            } while (x * x + y * y + z * z > 1 || y == 0);

            Vector3d dir(x, y, z);
            Ray photon_ray(offset, dir);

            trace_photon(scene, photon_ray, power, 0);
        }

        photon_map.balance();
        photon_map.scale_photon_power(1.0 / log(num_photons));
    }

    void trace_photon(const Scene& scene, Ray pr, Vec power, int depth) {

        if (depth >= max_reflect)
            return;

        double t;
        int id = 0;

        // find collision
        if (!scene.intersect(pr, t, id))
            return;

        const Drawable &obj = scene[id];

        Vector3d x   = pr.origin() + pr.dest() * t;
        Vector3d n   = (x - obj.position()).norm();
        Vector3d dir;
        Vector3d reflect_power;

        float nrand = rand_num(0, 1);
        photon_map.store(power, pr.origin(), pr.dest());

        // Diffuse
        if (nrand < pDiffuse){
            dir = diffuse_reflection(n);
            reflect_power = power * obj.color() / pDiffuse;
        }
        // Specular
        else if ((pDiffuse < nrand) && (nrand < (pDiffuse + pSpecular))){
            dir = pr.dest() - (n * n.dot(pr.dest())) * 2;
            reflect_power = power * obj.color() / pSpecular;
        }
        // absorb
        else{
            return ;
        }

        pr.set_origin(x);
        pr.set_dest(dir.norm());

        trace_photon(scene, pr, reflect_power, depth + 1);
    }

    Vector3d diffuse_reflection(Vector3d n) {
        float x, y, z;
        Vector3d dir;

        do {
            // new direction (rejection sampling)
            do {
                x = rand_num(0, 1);
                y = rand_num(0, 1);
                z = rand_num(0, 1);
            } while (x * x + y * y + z * z > 1);

            x   = 2 * (x - 0.5);
            y   = 2 * (y - 0.5);
            z   = 2 * (z - 0.5);

            dir = Vector3d(x, y, z);

        } while ((dir * n) >= 0);

        return dir;
    }


#endif

};
}

#endif
