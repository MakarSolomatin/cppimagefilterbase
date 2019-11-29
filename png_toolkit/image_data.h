#ifndef _image_data_h
#define _image_data_h

#include "stb_image.h"

struct image_data
{
    stbi_uc *pixels;
    int w, h;
    int compPerPixel;
};

struct image_rect
{
    int x, y, w, h;

    image_rect( int x = 0, int y = 0, int w = 0, int h = 0 ) : x(x), y(y), w(w), h(h) {
    }
};

#endif /*_image_data_h*/
