#ifndef RAYTRACING_ARENDER_HEADER_
#define RAYTRACING_ARENDER_HEADER_

#include <Vector.h>
#include <vector>

#include "Camera.h"
#include "Scene.h"
#include "PaintDevice.h"

namespace raytracing{


class AbstractRender
{
public:

    virtual Color shade(const Scene& scene, const Ray& r) = 0;

    virtual void render(const Scene& scene,
                        const Camera& camera,
                        PaintDevice& device) = 0;

};
}

#endif
