#ifndef RAYTRACING_PAINTDEVICE_HEADER_
#define RAYTRACING_PAINTDEVICE_HEADER_

#include "Color.h"

namespace raytracing{

enum ImageFormat{
    PPM
};

// A Device on which a RenderEngine can draw
// I don't know if this abstraction is worth it
class PaintDevice
{
public:
    typedef ColorT<int> Pixel;

    PaintDevice(int w, int h):
        _width(w), _height(h)
    {}

    int size  () const {    return _width * _height; }
    int width () const {    return _width;           }
    int height() const {    return _height;          }

    // used to draw
    virtual Pixel pixel(int i, int j) const = 0;
    virtual Pixel& pixel(int i, int j) = 0;

    // used to save
    virtual Pixel operator[] (int i) const = 0;
    virtual Pixel& operator[] (int i) = 0;

    // save rendered image to file
    void save_image(const char* name, ImageFormat = PPM){

        FILE *f = fopen(name, "w");
        PaintDevice& img = *this;

        fprintf(f, "P3\n%d %d\n%d\n", width(), height(), 255);

        for (int p = 0; p < size(); ++p) {
            fprintf(f, "%d %d %d ", img[p].x(), img[p].y(), img[p].z());
        }

        fclose(f);
    }

private:
    int _width;
    int _height;
};

}

#endif
