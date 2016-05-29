
#include "Render.h"
#include "Image.h"

using namespace raytracing;

int main(){

    Camera camera(
        Vector3d(0, 11.2, 214),
        Vector3d(0, -0.042612, -1).norm());

    Scene scene;

    Image img(1024, 768);

    raytracing::RTRender r;
        r.render(scene, camera, img);

    img.save_image("image.ppm");

    return 0;
}
