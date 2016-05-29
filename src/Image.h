#ifndef RAYTRACING_IMAGE_HEADER_
#define RAYTRACING_IMAGE_HEADER_

#include "Color.h"
#include "PaintDevice.h"

#include <vector>
#include <cstdio>

namespace raytracing{


// An image is a stupid vector of colors
class Image : public PaintDevice
{
public:
    Image(int w, int h):
        PaintDevice(w, h), _img(size())
    {}

    virtual Pixel  pixel(int i, int j) const {   return _img[i * col() + j]; }
    virtual Pixel& pixel(int i, int j)       {   return _img[i * col() + j]; }

    virtual Pixel  operator[] (int i) const  {   return _img[i]; }
    virtual Pixel& operator[] (int i)        {   return _img[i]; }

    int row() const {   return height(); }
    int col() const {   return width();  }

private:
    typedef std::vector<ColorT<int>> ImplImage;
    ImplImage _img;
};


}

#endif
