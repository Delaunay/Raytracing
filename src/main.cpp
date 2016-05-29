
#include "Render.h"
#include "Image.h"

using namespace raytracing;

int main(){

    Camera camera(
        Vector3d(0, 11.2, 214),
        Vector3d(0, -0.042612, -1).norm());

    Scene scene;
        scene.add_object<Sphere>( 1e5, Vector3d(-1e5 - 49, 0, 0),         Color(.75, .25, .25));
        scene.add_object<Sphere>( 1e5, Vector3d( 1e5 + 49, 0, 0),         Color(.25, .25, .75));

        scene.add_object<Sphere>( 1e5, Vector3d(   0,    0, -1e5 - 81.6), Color(.75, .75, .75));
        scene.add_object<Sphere>( 1e5, Vector3d(   0, -1e5 - 40.8, 0),    Color(.75, .75, .75));
        scene.add_object<Sphere>( 1e5, Vector3d(   0,  1e5 + 40.8, 0),    Color(.75, .75, .75));

        scene.add_object<Sphere>(16.5, Vector3d( -23, -24.3, -34.6),      Color(.999, .999, .999), Color(0, 0, 0), Specular);
        scene.add_object<Sphere>(16.5, Vector3d(  23, -24.3, -3.6),       Color(.100, .290, .999));
        scene.add_object<Sphere>( 8.5, Vector3d(   0,  24.3 , 0),         Color(0.171, 0.171, 0.171), Color(20, 20, 20));

    Image img(1024, 768);

    raytracing::RTRender r;
        r.render(scene, camera, img);

    img.save_image("image.ppm");

    return 0;
}
